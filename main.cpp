#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

/* -------------------- BASE CLASS -------------------- */
class Person {
protected:
    int id;
    string name;

public:
    Person(int id = 0, string name = "Unknown") {
        this->id = id;
        this->name = name;
    }

    virtual void display() {
        cout << "ID: " << id << "\nName: " << name << endl;
    }

    int getID() {
        return id;
    }
};

/* -------------------- DERIVED CLASS -------------------- */
class Student : public Person {
private:
    string emotion;
    float attentionLevel;

public:
    Student(int id = 0, string name = "Unknown")
        : Person(id, name) {
        emotion = "Not Detected";
        attentionLevel = 0.0;
    }

    void updateEmotion(string emo) {
        emotion = emo;
    }

    void updateAttention(float level) {
        attentionLevel = level;
    }

    float getAttention() {
        return attentionLevel;
    }

    void display() override {
        Person::display();
        cout << "Emotion: " << emotion << endl;
        cout << "Attention Level: " << attentionLevel << endl;
        cout << "-----------------------------\n";
    }
};

/* -------------------- CAMERA CLASS -------------------- */
class Camera {
public:
    void captureFrame() {
        cout << "Camera capturing frame...\n";
    }
};

/* -------------------- EMOTION DETECTOR -------------------- */
class EmotionDetector {
public:
    string detectEmotion() {
        int random = rand() % 4;

        switch (random) {
            case 0: return "Focused";
            case 1: return "Sleepy";
            case 2: return "Distracted";
            case 3: return "Happy";
        }
        return "Neutral";
    }
};

/* -------------------- ATTENTION ANALYZER -------------------- */
class AttentionAnalyzer {
public:
    float analyzeAttention(string emotion) {
        if (emotion == "Focused") return 0.9;
        if (emotion == "Happy") return 0.8;
        if (emotion == "Distracted") return 0.4;
        if (emotion == "Sleepy") return 0.2;
        return 0.5;
    }
};

/* -------------------- CLASSROOM CLASS -------------------- */
class Classroom {
private:
    Student* students;
    int totalStudents;
    int capacity;

    Camera camera;
    EmotionDetector detector;
    AttentionAnalyzer analyzer;

public:
    Classroom(int cap = 50) {
        capacity = cap;
        totalStudents = 0;
        students = new Student[capacity];   // Dynamic Memory
    }

    ~Classroom() {
        delete[] students;   // Destructor
    }

    void addStudent() {
        if (totalStudents >= capacity) {
            cout << "Classroom is full!\n";
            return;
        }

        int id;
        string name;

        cout << "Enter Student ID: ";
        cin >> id;
        cout << "Enter Student Name: ";
        cin >> name;

        students[totalStudents] = Student(id, name);
        totalStudents++;

        cout << "Student added successfully!\n";
    }

    void monitorClass() {
        if (totalStudents == 0) {
            cout << "No students to monitor!\n";
            return;
        }

        for (int i = 0; i < totalStudents; i++) {
            camera.captureFrame();

            string emo = detector.detectEmotion();
            float attention = analyzer.analyzeAttention(emo);

            students[i].updateEmotion(emo);
            students[i].updateAttention(attention);
        }

        cout << "Monitoring completed!\n";
    }

    void viewReport() {
        if (totalStudents == 0) {
            cout << "No students available!\n";
            return;
        }

        for (int i = 0; i < totalStudents; i++) {
            students[i].display();
        }
    }

    void classAverage() {
        if (totalStudents == 0) {
            cout << "No students available!\n";
            return;
        }

        float sum = 0;
        for (int i = 0; i < totalStudents; i++) {
            sum += students[i].getAttention();
        }

        cout << "Class Average Attention: "
             << (sum / totalStudents) << endl;
    }
};

/* -------------------- MAIN FUNCTION -------------------- */
int main() {

    Classroom classroom(50);
    int choice;

    do {
        cout << "\n===== Intelligent Classroom Monitoring System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Start Monitoring\n";
        cout << "3. View Student Attention Report\n";
        cout << "4. View Class Average Attention\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                classroom.addStudent();
                break;
            case 2:
                classroom.monitorClass();
                break;
            case 3:
                classroom.viewReport();
                break;
            case 4:
                classroom.classAverage();
                break;
            case 5:
                cout << "Exiting system...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}