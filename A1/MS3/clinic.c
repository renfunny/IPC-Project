/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Renato Cordova
Student ID#: 153325238
Email      : rcordova3@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt) {
    int i;
    if (patient == NULL) {
        printf("*** No records found ***\n");
    }
    else {
        displayPatientTableHeader();
        for (i = 0; i < max; i++) {
            if (patient[i].patientNumber != 0) {
                displayPatientData(&patient[i], fmt);
            }
        }
        printf("\n");
    }
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max) {
    int selection;

    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);
        printf("\n");

        switch (selection) {
        case 0:
            break;
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max) {
    int index;

    index = findPatientIndexByPatientNum(0, patient, max);

    if (index == -1) {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max) {
    int patientNumber, index;

    printf("Enter the patient number: ");
    patientNumber = inputIntPositive();
    printf("\n");

    index = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (index == -1) {
        printf("ERROR: Patient record not found!\n\n");
    }
    else {
        menuPatientEdit(&patient[index]);
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max) {
    int patientNumber, index;
    char options[2] = { 'y', 'n' }, selection;

    printf("Enter the patient number: ");
    patientNumber = inputIntPositive();
    printf("\n");

    index = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (index == -1) {
        printf("ERROR: Patient record not found!\n\n");
    }
    else {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
        printf("Are you sure you want to remove this patient record? (y/n): ");
        selection = inputCharOption(options);

        if (selection == 'y') {
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else {
            printf("Operation aborted.\n\n");
        }
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(const struct ClinicData* data){
    int i, index;

    displayScheduleTableHeader(NULL, 1);

for (i = 0; i < data->maxAppointments; i++) {
		if (data->appointments[i].date.year != 0) {
            index = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
			displayScheduleData(&data->patients[index], &data->appointments[i], 1);
		}
	}
    	printf("\n");
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData* data){
    struct Date date;
    int i, index;

    inputDate(&date);
    printf("\n");

    displayScheduleTableHeader(&date, 0);
    for (i = 0; i < data->maxAppointments; i++) {
        if (compareDates(data->appointments[i].date, date) == 0) {
			index = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
			displayScheduleData(&data->patients[index], &data->appointments[i], 0);
		}
    }
}

int compareDates(const struct Date date1, const struct Date date2) {
    int result = 0;

    if (date1.year != date2.year) {
        result = date1.year < date2.year ? -1 : 1;
    }
    if (date1.month != date2.month) {
        result = date1.month < date2.month ? -1 : 1;
    }
    if (date1.day != date2.day) {
        result = date1.day < date2.day ? -1 : 1;
    }

    return result;
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appoint, int maxAppointments, const struct Patient* patient, int maxPatients) {
    struct Date date;
    struct Time time;
    int patientNumber, i, index, flag = 0, dateInput = 0;

    printf("Patient Number: ");
    patientNumber = inputIntPositive();

    index = findPatientIndexByPatientNum(patientNumber, patient, maxPatients);

    if (index == -1) {
        printf("ERROR: Patient record not found!\n\n");
    }
    else {
        do {
            flag = 1;
            inputDate(&date);
            inputTime(&time);

            for (i = 0; i < maxAppointments; i++) {
                if (appoint[i].date.year == date.year && appoint[i].date.month == date.month && appoint[i].date.day == date.day) {
                    if (appoint[i].time.hour == time.hour && appoint[i].time.min == time.min) {
                        flag = 0;
                        break;
                    }
                }
            }

            if (!flag) {
                printf("ERROR: Appointment timeslot is not avaliable!\n\n");
            }
            else {
                for (i = 0; i < maxAppointments; i++) {
                    if (appoint[i].date.year == 0) {
                        appoint[i].date.year = date.year;
                        appoint[i].date.month = date.month;
                        appoint[i].date.day = date.day;
                        appoint[i].time.hour = time.hour;
                        appoint[i].time.min = time.min;
                        appoint[i].patientNumber = patientNumber;
                        printf("*** New appointment booked! ***\n\n");
                        dateInput = 1;
                        break;
                    }
                }
                if (!dateInput) {
                    printf("ERROR: Appointment listing is FULL!\n\n");
                }
            }
        } while (!flag);
    }
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appoint, int maxAppointments, const struct Patient* patient, int maxPatients) {
    char selection;
    int patientNumber, i, index, flag = 0;
    struct Date dateInput;

    printf("Patient Number: ");
    patientNumber = inputIntPositive();

    index = findPatientIndexByPatientNum(patientNumber, patient, maxPatients);

    if (index == -1) {
        printf("ERROR: Patient record not found!\n\n");
    }
    else {
        inputDate(&dateInput);
        printf("\n");

        for (i = 0; i < maxAppointments; i++) {
            if(appoint[i].date.year == dateInput.year && appoint[i].date.month == dateInput.month && appoint[i].date.day == dateInput.day) {
                displayPatientData(&patient[index], FMT_FORM);
                printf("Are you sure you want to remove this appointment? (y,n): ");
                selection = inputCharOption("yn");
                if (selection == 'y') {
                    appoint[i].date.year = 0;
                    printf("\n");
                    printf("Appointment record has been removed!\n\n");
                }
                else {
                    printf("Operation aborted.\n\n");
                }
                break;
			}
        }
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int patientNumber, index;
    printf("Search by patient number: ");
    patientNumber = inputIntPositive();
    printf("\n");

    index = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (index == -1) {
        printf("*** No records found ***\n\n");
    }
    else {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
    }

}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    int i, count = 0;
    char phoneNumber[11];

    printf("Search by phone number: ");
    inputCString(phoneNumber, 10, 10);
    printf("\n");

    displayPatientTableHeader();
    for (i = 0; i < max; i++) {
        if (strcmp(patient[i].phone.number, phoneNumber) == 0) {
            displayPatientData(&patient[i], FMT_TABLE);
            count++;
        }
    }
    if (count == 0) {
        printf("\n*** No records found ***\n\n");
    }
    else {
        printf("\n");
    }

}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max) {
    int i, highest = 0;

    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber > highest) {
            highest = patient[i].patientNumber;
        }
    }
    return highest + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) {
    int i, index = -1;

    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == patientNumber) {
            index = i;
            break;
        }
    }
    return index;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient) {
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone) {
    int selection;

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    printf("\n");

    switch (selection) {
    case 1:
        strcpy(phone->description, "CELL");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        printf("\n");
        break;
    case 2:
        strcpy(phone->description, "HOME");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        printf("\n");
        break;
    case 3:
        strcpy(phone->description, "WORK");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        printf("\n");
        break;
    case 4:
        strcpy(phone->description, "TBD");
        break;
    }

}

// Input date 
void inputDate(struct Date* date) {
    printf("Year        : ");
    date->year = inputInt();
    printf("Month (%d-%d): ", MIN_MONTH, MAX_MONTH);
    date->month = inputIntRange(MIN_MONTH, MAX_MONTH);

    if (date->month == 2) {
        if ((date->year % 4 == 0 && date->year % 100 != 0) || (date->year % 400 == 0)) {
            printf("Day (%d-%d)  : ", MIN_DAY, MAX_DAY_FEB_LEAP);
            date->day = inputIntRange(MIN_DAY, MAX_DAY_FEB_LEAP);
        } else {
            printf("Day (%d-%d)  : ", MIN_DAY, MAX_DAY_FEB);
            date->day = inputIntRange(MIN_DAY, MAX_DAY_FEB);
        }
    } else {
        printf("Day (%d-%d)  : ", MIN_DAY, MAX_DAY);
        date->day = inputIntRange(MIN_DAY, MAX_DAY);
    }
}

// Input time
void inputTime(struct Time* time) {
    int flag = 0;

    do {
        flag = 1;
        printf("Hour (0-23)  : ");
        time->hour = inputIntRange(0, 23);
        printf("Minute (0-59): ");
        time->min = inputIntRange(0, 59);

        if(((time->hour * 60) + time->min) < (APPOINTMENT_START * 60) || (((time->hour * 60) + time->min) > (APPOINTMENT_END * 60)) || time->min % APPOINTMENT_INTERVAL != 0) {
			printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", APPOINTMENT_START, APPOINTMENT_END, APPOINTMENT_INTERVAL);
			flag = 0;
		}

    } while (!flag);
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max) {
    int count = 0;
    FILE* fp = fopen(datafile, "r");
    if (fp == NULL) {
        printf("ERROR: Unable to open file %s\n", datafile);
        return 0;
    } else {

        while (count < max && fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", 
            &patients[count].patientNumber, 
            patients[count].name, 
            &patients[count].phone.description, 
            patients[count].phone.number) >= 3) {
            count++;
        }
        fclose(fp);

    }
    return count;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    int count = 0;
    FILE* fp = fopen(datafile, "r");

    if (fp == NULL) {
		printf("ERROR: Unable to open file %s\n", datafile);
		return 0;
	} else {

		while (count < max && fscanf(fp, "%d,%d,%d,%d,%d,%d\n", 
            &appoints[count].patientNumber,
			&appoints[count].date.year, 
			&appoints[count].date.month, 
			&appoints[count].date.day, 
			&appoints[count].time.hour, 
			&appoints[count].time.min) == 6) {
			count++;
		}
		fclose(fp);

	}
return count;
}