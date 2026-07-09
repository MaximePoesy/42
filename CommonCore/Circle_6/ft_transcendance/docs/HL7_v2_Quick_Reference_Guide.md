# Healthcare Data Integration: Key Concepts

This guide explains the core elements used in HL7 v2 and FHIR integration projects.

---

## 1. HL7 v2 Concepts (Legacy Standards)

_Used with the `hl7` Python library._

### **Segment**

The "row" of a message. Every HL7 v2 message is made of segments (e.g., `MSH`, `PID`, `PV1`). Each segment starts with a 3-letter code and handles a specific category of data.

### **Field (Separator: `|`)**

A specific data slot within a segment. For example, `PID-3` is the field for the Patient Identifier. In Python, accessed via the first index: `segment[3]`.

### **Component (Separator: `^`)**

A sub-division of a field. Many fields are complex (like a name or an address).

- _Example:_ `Doe^John` consists of two components: Family Name and Given Name.
- _Python index:_ `segment[field][repetition][component]`.

### **Repetition (Separator: `~`)**

Allows a field to have multiple values.

- _Example:_ A patient with two phone numbers would have them in the same field separated by `~`.

---

## 2. FHIR Concepts (Modern Standards)

_Used with the `fhir.resources` library._

### **Resource**

The fundamental unit of FHIR. Instead of segments, data is organized into specific "objects" like `Patient`, `Observation`, or `Medication`. Each resource has a fixed, documented JSON structure.

### **Bundle**

A container for a collection of resources. In an API context, you rarely send just one resource.

- **Usage:** If you search for "all patients named Smith," the server returns a **Bundle** containing multiple `Patient` resources.
- **Transaction:** You can wrap a `Patient` and their `Encounter` in a Bundle to save them both at the same time.

### **Reference**

How resources talk to each other. Unlike HL7 v2 where everything is in one text file, FHIR uses links.

- _Example:_ An `Observation` resource has a `subject` field that contains a **Reference** (a URL or ID) pointing to the `Patient` resource.

### **Element / BackboneElement**

The internal building blocks of a resource. For example, `Patient.contact` is a "BackboneElement" because it contains several sub-fields (name, relationship, phone).

### **CodeableConcept & Coding (Terminology)**

This is the core of medical interoperability. FHIR uses a nested structure to avoid ambiguity when identifying clinical concepts.

- **`code` (CodeableConcept):** The high-level concept (e.g., "Blood Glucose").
- **`coding` (List of Coding):** A list of translations for that concept into different standard systems (LOINC, SNOMED, or local codes).
- **`code` (the value):** The actual identifier within a specific system (e.g., `2339-0` in LOINC).
- **Why this structure?** It allows the same data to be understood by different systems worldwide, even if they use different medical dictionaries.

---

## 3. Python Infrastructure Concepts

_Used with `FastAPI`, `Uvicorn`, and `Pydantic`._

### **Model (Pydantic)**

A Python class that defines the "shape" of your data. When you use `fhir.resources`, you are using pre-built Pydantic models. They automatically validate that a date is a real date and a string is a string.

### **Endpoint (Route)**

The URL in your FastAPI app where data is sent or received (e.g., `POST /api/v1/hl7-ingest`).

### **Parser**

The logic (your code) that takes raw HL7 text, breaks it down using the `hl7` library, and maps it into a FHIR Resource or a Database.

---

## Summary Mapping

| Concept       | HL7 v2 Equivalent | FHIR Equivalent     |
| :------------ | :---------------- | :------------------ |
| **Data Unit** | Segment           | Resource            |
| **Container** | Message           | Bundle              |
| **Sub-data**  | Component (`^`)   | Attribute / Element |
| **Identity**  | PID-3             | Resource.id         |

---

# HL7 v2 Quick Reference Guide (MSH, PID, PV1)

This guide provides a mapping of the most common fields used in HL7 v2.x segments for healthcare interoperability.

---

## 1. MSH - Message Header

_The MSH segment defines the message's origin, destination, time, and type._

| Field      | Name                  | Description / Example                             |
| :--------- | :-------------------- | :------------------------------------------------ | --- |
| **MSH-1**  | Field Separator       | Usually `                                         | `   |
| **MSH-2**  | Encoding Characters   | Usually `^~\&`                                    |
| **MSH-3**  | Sending Application   | Name of the source system (e.g., `HIS`)           |
| **MSH-4**  | Sending Facility      | The hospital/site sending the data                |
| **MSH-5**  | Receiving Application | Name of the destination system (e.g., `EMR`)      |
| **MSH-6**  | Receiving Facility    | The hospital/site receiving the data              |
| **MSH-7**  | Date/Time of Message  | Format: `YYYYMMDDHHMMSS`                          |
| **MSH-9**  | Message Type          | `Type^Event` (e.g., `ADT^A01` or `ORM^O01`)       |
| **MSH-10** | Message Control ID    | Unique ID for tracking this specific message      |
| **MSH-11** | Processing ID         | `P` (Production), `D` (Debugging), `T` (Training) |
| **MSH-12** | Version ID            | HL7 version (e.g., `2.3`, `2.4`, `2.5`)           |

---

## 2. PID - Patient Identification

_The PID segment contains the patient's demographic and primary identifying information._

| Field      | Name                    | Description / Example                                        |
| :--------- | :---------------------- | :----------------------------------------------------------- |
| **PID-1**  | Set ID                  | Sequence number (usually `1`)                                |
| **PID-3**  | Patient Identifier List | `ID^CheckDigit^Code^AssigningAuth` (e.g., `12345^^^HOSP^MR`) |
| **PID-5**  | Patient Name            | `LastName^FirstName^MiddleName`                              |
| **PID-7**  | Date/Time of Birth      | Format: `YYYYMMDD`                                           |
| **PID-8**  | Administrative Sex      | `M` (Male), `F` (Female), `U` (Unknown)                      |
| **PID-10** | Race                    | Patient's race code                                          |
| **PID-11** | Patient Address         | `Street^^City^State^Zip`                                     |
| **PID-13** | Phone Number (Home)     | Primary contact number                                       |
| **PID-18** | Patient Account Number  | The billing account number                                   |
| **PID-19** | SSN / National ID       | Social Security Number                                       |

---

## 3. PV1 - Patient Visit

_The PV1 segment contains information about the patient's stay or encounter._

| Field      | Name                      | Description / Example                                    |
| :--------- | :------------------------ | :------------------------------------------------------- |
| **PV1-1**  | Set ID                    | Sequence number (usually `1`)                            |
| **PV1-2**  | Patient Class             | `I` (Inpatient), `O` (Outpatient), `E` (Emergency)       |
| **PV1-3**  | Assigned Patient Location | `PointOfCare^Room^Bed` (e.g., `ICU^102^A`)               |
| **PV1-4**  | Admission Type            | `A` (Accident), `E` (Emergency), `L` (Labor)             |
| **PV1-7**  | Attending Physician       | `ID^LastName^FirstName`                                  |
| **PV1-8**  | Referring Physician       | The doctor who referred the patient                      |
| **PV1-10** | Hospital Service          | Department code (e.g., `CARD` for Cardiology)            |
| **PV1-14** | Admit Source              | Where the patient came from                              |
| **PV1-18** | Patient Type              | Specific category of patient                             |
| **PV1-19** | Visit Number              | Unique encounter/stay ID (often used as the primary key) |
| **PV1-44** | Admit Date/Time           | Format: `YYYYMMDDHHMMSS`                                 |
| **PV1-45** | Discharge Date/Time       | Format: `YYYYMMDDHHMMSS`                                 |

---

## Developer Tip: Deep Indexing in Python

When using the `hl7` library in Python, remember the nested list structure:

- **Field:** `segment[index]`
- **Repetition:** `segment[index][repetition]`
- **Component:** `segment[index][repetition][component]`

**Example:** To get the Patient's Last Name: `pid_segment[5][0][0]`

---

[
['PID'], # [0]
['1'], # [1]
[''], # [2]
[ # [3] <-- Repetition list
[ # [3][0] <-- Components list
'123456', # [3][0][0] <-- Value (String)
'', # [3][0][1]
'', # [3][0][2]
'HOSP', # [3][0][3]
'MR' # [3][0][4]
]
]
]

---
