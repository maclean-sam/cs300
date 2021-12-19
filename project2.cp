// Name: Samuel Maclean
// School: Southern New Hampshire University
// Course: CS-300: Analysis and Design
// Assignment: Project 2 
// Date: 12/08/2021


#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

// Global Definitions
// 
// define a structure to hold Course information
struct Course {
    string courseId; // unique identifier
    string title;
    string prerequisite1;
    string prerequisite2;
};

//Display course information
void displayCourse(Course course) {
    cout << course.courseId << ", " << course.title << endl;
    return;
}


vector<Course> loadCourses(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);


    vector<Course> courses; //create new vector of courses
    // read and display header row 
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            Course course;
            course.courseId = file[i][0];
            course.title = file[i][1];
            course.prerequisite1 = file[i][2];
            course.prerequisite2 = file[i][3];

            //cout << "COURSE " << i << " COURSE INFO: " << course.courseId << course.title << endl;

            // push this course to the end
            courses.push_back(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
    return courses;
}

//Partition the vector of courses alphabetically
int partition(vector<Course>& courses, int begin, int end) {
    //set low and high equal to begin and end
    int low = begin; //Initialize variables
    int high = end;
    unsigned int mid;
    int done = 0;

    //Pick the middle element as the pivot point
    mid = (begin + (end - begin) / 2);

    //While not done 
    while (done != 1) {
        //Increment low index while lowest Course is less than the mid point
        while (courses[low].courseId.compare(courses[mid].courseId) < 0) {
            ++low;
        }
        //Decrement high index while mid point is less than the high
        while (courses[mid].courseId.compare(courses[high].courseId) < 0) {
            --high;
        }

        if (low >= high) { //Checks if there are no elements remaining
            done = 1; //if so, while loop is exited
        }

        else {
            swap(courses[low], courses[high]); //Swap the courses
            ++low; //Move low and high courses closer
            --high;
        }
    }
    return high;
}

//Partition the vector of courses numerically
int partitionCourseNum(vector<Course>& courses, int begin, int end) {
    //set low and high equal to begin and end
    int low = begin; //Initialize variables
    int high = end;
    unsigned int mid;
    int done = 0;

    //Pick the middle element as the pivot point
    mid = (begin + (end - begin) / 2);

    //While not done 
    while (done != 1) {
        //Increment low index while lowest Course is less than the mid point
        while (courses[low].courseId.substr(4, 5).compare(courses[mid].courseId.substr(4, 5)) < 0) {
            ++low;
        }
        //Decrement high index while mid point is less than the high
        while (courses[mid].courseId.substr(4, 5).compare(courses[high].courseId.substr(4, 5)) < 0) {
            --high;
        }

        if (low >= high) { //Checks if there are no elements remaining
            done = 1; //if so, while loop is exited
        }

        else {
            swap(courses[low], courses[high]); //Swap the courses
            ++low; //Move low and high courses closer
            --high;
        }
    }
    return high;
}


//Quick sort alphabetically
void quickSort(vector<Course>& courses, int begin, int end) {
    //Set mid equal to 0
    unsigned int mid = 0;

    //Base case: stops running if vector is sorted
    if (begin >= end) {
        return;

    }

    /* Partition courses into low and high such that
     midpoint is location of last element in low */
    mid = partition(courses, begin, end);


    // recursively sort low partition (begin to mid)
    quickSort(courses, begin, mid);
    // recursively sort high partition (mid+1 to end)
    quickSort(courses, mid + 1, end);

}

//Quick sort numerically
void quickSortCourseNum(vector<Course>& courses, int begin, int end) {
    //Set mid equal to 0
    unsigned int mid = 0;

    //Base case: stops running if vector is sorted
    if (begin >= end) {
        return;

    }

    /* Partition courses into low and high such that
     midpoint is location of last element in low */
    mid = partitionCourseNum(courses, begin, end);


    // recursively sort low partition (begin to mid)
    quickSortCourseNum(courses, begin, mid);
    // recursively sort high partition (mid+1 to end)
    quickSortCourseNum(courses, mid + 1, end);

}

// Prints out the information for a specific course
void printCourseInformation(vector<Course>& courses) {
    
    cout << "Which course would you like to find information about?" << endl;
    cout << "(Example format: CSCI100)" << endl;

    // Get user input (course id)
    string course;
    cin >> course;

    bool courseFound = false;

    // For all courses
    for (int i = 0; i < courses.size(); ++i) {

        // If course found
        if (courses[i].courseId.compare(course) == 0) {

            courseFound = true;

            // If two prerequisites exist for course
            if ((courses[i].prerequisite1 != " ") && (courses[i].prerequisite2 != " ")) {
                // Print the course information and prerequisites
                cout << courses[i].courseId << ", " << courses[i].title << endl;
                cout << "Prerequisites: " << courses[i].prerequisite1 << ", " << courses[i].prerequisite2 << endl;
            }

            // If one prerequisite exists for course
            else if ((courses[i].prerequisite1 != " ") && (courses[i].prerequisite2 == " ")) {
                // Print the course information and only prerequisite
                cout << courses[i].courseId << ", " << courses[i].title << endl;
                cout << "Prerequisites: " << courses[i].prerequisite1 << endl;
            }

            else {
                cout << courses[i].courseId << ", " << courses[i].title << endl;
                cout << "Prerequisites: None" << endl;
            }
             
        }
    }
}






/**
 * main() method with menu implementation
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, courseKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        courseKey = "CSCI100"; //courseKey in csv file
        break;
    case 3:
        csvPath = argv[1];
        courseKey = argv[2];
        break;
    default:
        csvPath = "Courses.csv";
        courseKey = "CSCI100"; //courseKey in csv file
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the courses
    vector<Course> courses;

    //Display menu
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            // Initialize a timer variable before loading courses
            ticks = clock();

            // Complete the method call to load the courses
            courses = loadCourses(csvPath);

            cout << courses.size() << " courses read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:

            quickSortCourseNum(courses, 0, courses.size() - 1); //sort numerically
            quickSort(courses, 0, courses.size() - 1); //sort alphabetically

            for (int i = 0; i < courses.size(); ++i) {
                displayCourse(courses[i]); //display all courses
            }
            
            break;

        case 3:

            printCourseInformation(courses);
            break;

        default:
            // If invalid input
            cout << "Error: Please reload the bids and try again" << endl;
        }


    }

    cout << "Thank you for using the course planner!" << endl;

    return 0;
}
