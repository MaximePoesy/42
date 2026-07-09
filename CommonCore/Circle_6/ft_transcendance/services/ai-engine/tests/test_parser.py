import os
import pytest
from app.parsers.hl7_parser import parse_hl7_to_fhir, HL7ParsingError
from fhir.resources.bundle import Bundle

DATA_DIR = os.path.join(os.path.dirname(__file__), "data")

def load_fixture(filename: str) -> str:
    with open(os.path.join(DATA_DIR, filename), "r") as f:
        return f.read()

def test_valid_full_parsing():
    """Test parsing a complete and valid HL7 message."""
    hl7_text = load_fixture("valid_full.hl7")
    bundle = parse_hl7_to_fhir(hl7_text)
    
    assert isinstance(bundle, Bundle)
    assert bundle.type == "collection"
    assert len(bundle.entry) == 2 # Patient + Encounter (PV1)
    
    patient = [e.resource for e in bundle.entry if type(e.resource).__name__ == "Patient"][0]
    assert type(patient).__name__ == "Patient"
    
    # Check Identifier
    assert patient.identifier[0].value == "123456"
    
    # Check Name
    assert patient.name[0].family == "DOE"
    assert patient.name[0].given[0] == "JOHN"
    
    # Check DOB
    assert str(patient.birthDate) == "1980-05-15"
    
    # Check Gender
    assert patient.gender == "male"
    
    # Check Telecom
    assert patient.telecom[0].value == "555-123-4567"

def test_missing_fields_parsing():
    """Test parsing an HL7 message with a PID segment but missing many fields."""
    hl7_text = load_fixture("missing_fields.hl7")
    bundle = parse_hl7_to_fhir(hl7_text)
    
    assert len(bundle.entry) == 1
    patient = bundle.entry[0].resource
    
    assert patient.identifier[0].value == "789012"
    assert patient.name[0].family == "UNKNOWN_PATIENT"
    
    # Missing fields should not crash and should not be populated
    assert getattr(patient, "birthDate", None) is None
    assert patient.gender == "unknown"  # Default fallback
    assert getattr(patient, "telecom", None) is None

def test_invalid_date_parsing():
    """Test parsing an HL7 message with a malformed date."""
    hl7_text = load_fixture("invalid_date.hl7")
    bundle = parse_hl7_to_fhir(hl7_text)
    
    patient = bundle.entry[0].resource
    # It should catch the ValueError, log a warning, and skip the birthDate
    assert getattr(patient, "birthDate", None) is None
    assert patient.gender == "female" # Check that it continued parsing after error

def test_no_pid_segment():
    """Test parsing a valid HL7 message that lacks a PID segment."""
    hl7_text = load_fixture("no_pid.hl7")
    bundle = parse_hl7_to_fhir(hl7_text)
    
    # It should successfully return an empty bundle
    assert isinstance(bundle, Bundle)
    assert len(bundle.entry) == 0

def test_malformed_hl7_throws_error():
    """Test that complete garbage text raises the custom HL7ParsingError."""
    hl7_text = load_fixture("malformed.hl7")
    
    with pytest.raises(HL7ParsingError) as exc_info:
        parse_hl7_to_fhir(hl7_text)
        
    assert "Invalid HL7 message structure" in str(exc_info.value)

def test_empty_string_throws_error():
    """Test that an empty string raises the custom HL7ParsingError."""
    with pytest.raises(HL7ParsingError) as exc_info:
        parse_hl7_to_fhir("   \n  ")
        
    assert "Empty HL7 message provided" in str(exc_info.value)

def test_complex_1_parsing():
    """Test parsing a complex HL7 message (ADT^A08) with multiple segments."""
    hl7_text = load_fixture("complex_1.hl7")
    bundle = parse_hl7_to_fhir(hl7_text)
    
    assert len(bundle.entry) == 3 # Patient + Encounter + Observation
    patient = [e.resource for e in bundle.entry if type(e.resource).__name__ == "Patient"][0]
    
    assert patient.identifier[0].value == "999888777"
    assert patient.name[0].family == "O'CONNOR"
    assert patient.name[0].given[0] == "SARAH"
    assert str(patient.birthDate) == "1992-08-24"
    assert patient.gender == "female"
    assert patient.telecom[0].value == "(555)555-9876"
    
    # Check Encounter (from PV1)
    encounters = [e.resource for e in bundle.entry if type(e.resource).__name__ == "Encounter"]
    assert len(encounters) == 1
    # Check that class is correctly mapped (nested inside coding)
    assert encounters[0].class_fhir[0].coding[0].code == "inpatient"

    # Check OBX (Observation)
    observations = [e.resource for e in bundle.entry if type(e.resource).__name__ == "Observation"]
    assert len(observations) == 1
    assert observations[0].code.coding[0].code == "WBC"
    assert observations[0].valueQuantity.value == 8.5
    assert observations[0].valueQuantity.unit == "10^3/uL"

def test_complex_2_parsing():
    """Test parsing a complex HL7 message (ORU^R01) with lab results."""
    hl7_text = load_fixture("complex_2.hl7")
    bundle = parse_hl7_to_fhir(hl7_text)
    
    assert len(bundle.entry) == 5 # 1 Patient + 4 OBX
    patient = bundle.entry[0].resource
    
    assert patient.identifier[0].value == "555444333"
    assert patient.name[0].family == "SMITH-JONES"
    
    observations = [e.resource for e in bundle.entry if type(e.resource).__name__ == "Observation"]
    assert len(observations) == 4
    # Check specifically the first observation (Cholesterol)
    assert observations[0].code.coding[0].display == "Cholesterol"
    assert observations[0].valueQuantity.value == 190.0
    assert observations[0].valueQuantity.unit == "mg/dL"

def test_multiple_names_parsing():
    """Test that the parser picks the first name when multiple names are provided (repeating fields)."""
    hl7_text = load_fixture("multiple_names.hl7")
    bundle = parse_hl7_to_fhir(hl7_text)
    
    patient = bundle.entry[0].resource
    # It should pick the first repetition (DOE^JOHN) and ignore SMITH^JANE
    assert patient.name[0].family == "DOE"
    assert patient.name[0].given[0] == "JOHN"

def test_invalid_gender_fallback():
    """Test that non-standard gender codes fallback to 'unknown' in FHIR."""
    hl7_text = load_fixture("invalid_gender.hl7")
    bundle = parse_hl7_to_fhir(hl7_text)
    
    patient = bundle.entry[0].resource
    # HL7 code 'X' is not M, F, O, or U, so it should map to 'unknown'
    assert patient.gender == "unknown"
