import logging
from datetime import datetime
from typing import Optional, List, Dict, Any

import hl7
from pydantic import ValidationError

from fhir.resources.patient import Patient
from fhir.resources.bundle import Bundle
from fhir.resources.observation import Observation
from fhir.resources.encounter import Encounter
from fhir.resources.codeableconcept import CodeableConcept
from fhir.resources.quantity import Quantity

# Configure module logger
logger = logging.getLogger(__name__)

class HL7ParsingError(Exception):
    """Custom exception raised when HL7 to FHIR parsing fails."""
    pass

def _safe_get_field(segment: hl7.Segment, field_idx: int, comp_idx: int = 0, sub_comp_idx: int = 0) -> str:
    """
    Safely extract a value from an HL7 segment to avoid IndexError.
    """
    try:
        if len(segment) > field_idx:
            field = segment[field_idx]
            if isinstance(field, str):
                return field.strip() if comp_idx == 0 and sub_comp_idx == 0 else ""
                
            if len(field) > 0:
                rep = field[0]
                if isinstance(rep, str):
                    return rep.strip() if comp_idx == 0 and sub_comp_idx == 0 else ""
                    
                if len(rep) > comp_idx:
                    comp = rep[comp_idx]
                    if isinstance(comp, str):
                        return comp.strip() if sub_comp_idx == 0 else ""
                        
                    if len(comp) > sub_comp_idx:
                        return str(comp[sub_comp_idx]).strip()
    except (IndexError, AttributeError):
        pass
    return ""

def _safe_get_raw_field(segment: hl7.Segment, field_idx: int) -> str:
    """
    Return the full raw text of an HL7 field, components included.

    Unlike _safe_get_field (which returns only the first component), this keeps
    the whole field as written. Needed for units like "10^3/uL" where the unit
    itself contains '^' — the HL7 component separator — and would otherwise be
    truncated to "10".
    """
    try:
        if len(segment) > field_idx:
            return str(segment[field_idx]).strip()
    except (IndexError, AttributeError):
        pass
    return ""

def _parse_pid_to_patient(pid_segment: hl7.Segment) -> Optional[Patient]:
    """
    Maps an HL7 PID (Patient Identification) segment to a FHIR Patient resource.
    """
    try:
        patient_data: Dict[str, Any] = {}
        patient_id = _safe_get_field(pid_segment, 3)
        if patient_id:
            patient_data["identifier"] = [{"value": patient_id}]

        family_name = _safe_get_field(pid_segment, 5, 0)
        given_name = _safe_get_field(pid_segment, 5, 1)
        
        name_obj: Dict[str, Any] = {}
        if family_name:
            name_obj["family"] = family_name
        if given_name:
            name_obj["given"] = [given_name]
        if name_obj:
            patient_data["name"] = [name_obj]

        dob_str = _safe_get_field(pid_segment, 7)
        if dob_str:
            try:
                parsed_date = datetime.strptime(dob_str[:8], "%Y%m%d").date()
                patient_data["birthDate"] = parsed_date.isoformat()
            except ValueError:
                logger.warning(f"Invalid birth date format in HL7 message: {dob_str}")

        gender_code = _safe_get_field(pid_segment, 8).upper()
        gender_map = {'M': 'male', 'F': 'female', 'O': 'other', 'U': 'unknown'}
        patient_data["gender"] = gender_map.get(gender_code, "unknown")

        phone = _safe_get_field(pid_segment, 13)
        if phone:
            patient_data["telecom"] = [{"system": "phone", "value": phone, "use": "home"}]

        return Patient(**patient_data)
    except Exception as e:
        logger.error(f"Error parsing PID segment: {e}")
        return None

def _parse_obx_to_observation(obx_segment: hl7.Segment) -> Optional[Observation]:
    """
    Maps an HL7 OBX (Observation/Result) segment to a FHIR Observation resource.
    """
    try:
        obs_data: Dict[str, Any] = {
            "status": "final", # Default for OBX
            "category": [{"coding": [{"system": "http://terminology.hl7.org/CodeSystem/observation-category", "code": "vital-signs"}]}]
        }

        # 1. Observation Code (OBX-3)
        code = _safe_get_field(obx_segment, 3, 0)
        display = _safe_get_field(obx_segment, 3, 1)
        if code:
            obs_data["code"] = {"coding": [{"code": code, "display": display}]}

        # 2. Value (OBX-5) and Units (OBX-6)
        value_str = _safe_get_field(obx_segment, 5)
        units = _safe_get_raw_field(obx_segment, 6)
        
        # Determine value type (Number vs String)
        try:
            value_float = float(value_str)
            obs_data["valueQuantity"] = {"value": value_float, "unit": units}
        except ValueError:
            obs_data["valueString"] = value_str

        # 3. Reference Range (OBX-7)
        ref_range = _safe_get_field(obx_segment, 7)
        if ref_range:
            obs_data["referenceRange"] = [{"text": ref_range}]

        return Observation(**obs_data)
    except Exception as e:
        logger.error(f"Error parsing OBX segment: {e}")
        return None

def _parse_pv1_to_encounter(pv1_segment: hl7.Segment) -> Optional[Encounter]:
    """
    Maps an HL7 PV1 (Patient Visit) segment to a FHIR Encounter resource.
    """
    try:
        encounter_data: Dict[str, Any] = {"status": "finished"}
        
        # Patient Class (PV1-2)
        patient_class = _safe_get_field(pv1_segment, 2)
        class_map = {'I': 'inpatient', 'O': 'outpatient', 'E': 'emergency'}
        if patient_class in class_map:
            # Wrap in a list of CodeableConcepts as required by this library version
            encounter_data["class_fhir"] = [{
                "coding": [{
                    "code": class_map[patient_class], 
                    "system": "http://terminology.hl7.org/CodeSystem/v3-ActCode"
                }]
            }]

        # Assigned Patient Location (PV1-3)
        location = _safe_get_field(pv1_segment, 3, 0)
        if location:
            encounter_data["location"] = [{"location": {"display": location}}]

        return Encounter(**encounter_data)
    except Exception as e:
        logger.error(f"Error parsing PV1 segment: {e}")
        return None

def parse_hl7_to_fhir(hl7_message: str) -> Bundle:
    """
    Converts an HL7 v2 message into a FHIR R4 Bundle, now supporting OBX and PV1.
    """
    if not hl7_message or not hl7_message.strip():
        raise HL7ParsingError("Empty HL7 message provided.")

    normalized_message = hl7_message.replace('\n', '\r').strip()
    try:
        parsed_hl7 = hl7.parse(normalized_message)
    except Exception as e:
        raise HL7ParsingError(f"Invalid HL7 message structure: {e}")

    entries = []

    # 1. Process Patient (PID)
    try:
        pid = parsed_hl7.segment("PID")
        patient = _parse_pid_to_patient(pid)
        if patient:
            entries.append({"resource": patient.model_dump(exclude_none=True)})
    except KeyError: pass

    # 2. Process Encounter (PV1)
    try:
        pv1 = parsed_hl7.segment("PV1")
        encounter = _parse_pv1_to_encounter(pv1)
        if encounter:
            entries.append({"resource": encounter.model_dump(exclude_none=True)})
    except KeyError: pass

    # 3. Process All Observations (OBX) - Multiple segments allowed
    for segment in parsed_hl7:
        if str(segment[0]) == "OBX":
            observation = _parse_obx_to_observation(segment)
            if observation:
                entries.append({"resource": observation.model_dump(exclude_none=True)})

    bundle_data = {"type": "collection", "entry": entries}
    try:
        return Bundle(**bundle_data)
    except ValidationError as ve:
        logger.error(f"FHIR Bundle validation failed: {ve}")
        raise HL7ParsingError("Failed to build a valid FHIR Bundle.")