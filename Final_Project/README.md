# Student Cyber Security Management System

A menu-driven C application developed as part of the internship final project. The system manages student records and provides basic cyber security utilities such as security assessment, password strength checking, and username generation.

---

## Objective

This project combines the core programming concepts learned during the internship:

* Variables
* Input / Output
* Conditional Statements
* Loops
* Functions
* Arrays
* File Handling
* Problem Solving

The application stores student records, performs security assessments, and generates reports through a simple command-line interface.

---

## Features

### Student Management

#### Add Student

Store the following details:

* Student ID
* Student Name
* Branch
* Email Address

#### View Students

Display all stored student records.

#### Search Student

Search students using:

* Student ID
* Student Name

#### Delete Student

Remove a student record from storage.

---

### Security Assessment

Evaluates a student's security practices based on:

* Multi-Factor Authentication (MFA)
* Password Length
* System Updates
* Antivirus Installation

Generates:

* Security Score (0–100)
* Security Status

Categories:

* Excellent
* Good
* Moderate
* Poor

---

### Report Generation

Generates a summary report containing:

* Total Students
* Security Scores
* Average Security Score
* Students with Poor Security Ratings

---

### Cyber Security Tools

#### Password Strength Checker

Analyzes password complexity and classifies it as:

* Strong
* Medium
* Weak

#### Username Generator

Automatically generates a username from a user's full name.

#### Login Validation

Provides basic authentication before accessing the system.

Default Credentials:

```text
Username: admin
Password: admin123
```

---

## File Storage

Student records are stored in:

```text
students.txt
```

Supported operations:

* Save Records
* Read Records
* Delete Records

---

## Project Structure

```text
Final_Project/
│
├── student_security_manager.c
├── students.txt (generated)
├── screenshot/
│   ├── Screenshot 1.png
│   ├── Screenshot 2.png
│   └── ...
└── README.md
```

---

## Sample Menu

```text
==========================
 Student Security Manager
==========================

1. Add Student
2. View Students
3. Search Student
4. Delete Student
5. Security Assessment
6. Generate Report
7. Cyber Security Tools
8. Exit
```

---

## Screenshots

### Login 

User successfully logs into the system and adds a new student record.

![Login ](screenshot/Screenshot%202026-06-22%20113308.png)

---
### Add Student

User successfully logs into the system and adds a new student record.

![Add Student](screenshot/Screenshot%202026-06-22%20113532.png)

---

### View Students

Displays all student records stored in the system.

![View Students](screenshot/Screenshot%202026-06-22%20113606.png)

---

### Search Student

Searches for a student using Student ID or Name and displays the matching record.

![Search Student](screenshot/Screenshot%202026-06-22%20113628.png)

---

### Delete Student

Deletes a student record from the system and displays a confirmation message.

![Delete Student](screenshot/Screenshot%202026-06-22%20113811.png)

---

### Security Assessment

Evaluates security practices and generates a security score with a status.

![Security Assessment](screenshot/Screenshot%202026-06-22%20113929.png)

---

### Generate Report

Displays the total number of students, security scores, average score, and poor ratings.

![Generate Report](screenshot/Screenshot%202026-06-22%20114039.png)

---

### Cyber Security Tools

Demonstrates:
- Password Strength Checker
- Username Generator

![Cyber Security Tools](screenshot/Screenshot%202026-06-22%20114208.png)

---

### Exit Program

Exits the Student Security Management System.

![Exit Program](screenshot/Screenshot%202026-06-22%20114230.png)
---

## Technologies Used

* C Programming Language
* Standard C Libraries
* File Handling
* Command Line Interface (CLI)

---

## Compilation

```bash
gcc student_security_manager.c -o student_security_manager
```

---

## Execution

### Linux / macOS

```bash
./student_security_manager
```

### Windows

```bash
student_security_manager.exe
```
