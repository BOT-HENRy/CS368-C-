/*******************************************************************************
 * Author:        Yizhe Qu	
 * CS Login:      qu
 * 
 * Pair Partner:  (name of your pair programming partner, if applicable)
 * CS Login:      (your partner's CS login name)
 * 
 * Credits:       none
 * 
 * Course:        CS 368, Fall 2015
 * Assignment:    Programming Assignment 2
 ******************************************************************************/
 
#include <iostream>
#include <algorithm> 
#include "SortedList.h"

using namespace std;

SortedList::SortedList(){
    head = NULL;
}

bool SortedList::insert(Student *s){
    int check = 0;
    Listnode *curP = head;
    //if list is empty
    if(head == NULL){
       Listnode *curr = new Listnode;
       curr->next = NULL;
       curr->student = s;
       head = curr;
       return true; 
    }
    //searching through the list
    if(find(s->getID()) == NULL){
        curP = head;
        //when head needs to be replaced
        if(head->student->getID() > s->getID()){
            Listnode *curr = new Listnode;
            curr->next = head;
            curr->student = s;
            head = curr;
            return true;
        }
        //when there's only one and needs to add at next
        if(curP->next == NULL && curP->student->getID() < s->getID()){
            Listnode *curr = new Listnode;
            curr->next = NULL;
            curr->student = s;
            curP->next = curr;
            return true;
        }
        //or search to find the position
        while(curP->next != NULL){
            if(curP->next->student->getID() > s->getID()){
                Listnode *curr = new Listnode;
                curr->next = curP->next;
                curr->student = s;
                curP->next = curr;
                return true;
            }   
            curP = curP->next;
            //if need to insert at last position
            if(curP->next == NULL){
                Listnode *curr = new Listnode;
                curr->next = NULL;
                curr->student = s;
                curP->next = curr;
                return true;
            } 
        }
    }else{
        check = 0;
        return false;
    }
}

Student * SortedList::find(int studentID){
    Listnode *curP = head;
    while(curP != NULL){        
        if(curP->student->getID() == studentID){
            return curP->student;
        }
        curP = curP->next;
    }
    return NULL;
}

Student * SortedList::remove(int studentID){
    Listnode *curP = head;
    Student *stu = new Student;
    //if head is what we want
    if(head->student->getID() == studentID){
        stu = head->student;
        head = curP->next;
        return stu;
    }
    //if only 2 in the list and need to remove the second one
    if(curP->next->next == NULL && curP->next->student->getID() == studentID){
        stu = head->next->student;
        head->next = NULL;
        return stu;
    }
    //or go through
    while(curP->next->next != NULL){
        if(curP->next->student->getID() == studentID){
            stu = curP->next->student;
            curP->next = curP->next->next;
            return stu;
        }   
        curP = curP->next;
        //if need to remove at last position
        if(curP->next->next == NULL){
            if(curP->next->student->getID() == studentID){
                stu = curP->next->student;
                curP->next = NULL;
                return stu;
            }
        }
    }
    return NULL;
}

int SortedList::getNStudents(int courseNumber, int inYear, Semester inSemester){
    int numStu = 0;
    Listnode *curP = head;
    while(curP != NULL){
        if(curP->student->tookCourse(courseNumber, inYear, inSemester)){
            numStu++;
        }
        curP = curP->next;
    }
    return numStu;
}

Student ** SortedList::getClassRoster(int courseNumber, int inYear, Semester inSemester){
    Student **stuHead = new Student*[getNStudents(courseNumber, inYear, inSemester)];
    Listnode *curP = head;
    int i = 0;
    while(curP != NULL){
        if(curP->student->tookCourse(courseNumber, inYear, inSemester)){
            stuHead[i] = curP->student;
            i++;
        }
        curP = curP->next;
    }
    stuHead[i] = NULL;
    return stuHead;
}



void SortedList::printClassRoster(int courseNumber, int inYear, Semester inSemester){
    Student **stuClass = getClassRoster(courseNumber, inYear, inSemester);
    if(stuClass == NULL){
        cout<< "Course " << courseNumber << " was not offered in " << inSemester << " of " << inYear << "." << endl;
    }else{
        int i = 0;
        while(stuClass[i] != NULL){
            cout<< stuClass[i]->getID() <<endl;
            i++;
        }
    }
}

void SortedList::printClassmates(int * studentGroup, int nStudents){

    int *currL = new int[nStudents];
    int index = 0;
    int check = 0;
    for(int i = 0; i < nStudents; i++){
        if(find(studentGroup[i]) != NULL){
            currL[index] = studentGroup[i];
            index++;
        }
    }
    for(int i = 0; i < index-2; i++){
        Student *stu1 = this->find(studentGroup[i]);
        CourseInfo const **currCourse = stu1->getCourses();
        for(int j = i+1; j < index-1; j++){
            Student *stu2 = this->find(studentGroup[j]);
            int k = 0;
            while(currCourse[k]!=NULL){
cout<<"1 time"<<endl;
                if(stu2->tookCourse(currCourse[k]->courseNumber,currCourse[k]->year,currCourse[k]->cSemester)){
                    cout<< "(" << currL[i] << "," << currL[j] << ")" <<endl;
                    check++;
                }
            }
        }
    }
    if(check == 0){
        cout<< "Cannot find a valid pair.\n";
    }

}


void SortedList::print() const{
    Listnode *curP = head;
    if(curP == NULL){
        cout<< "Empty student list.\n";
    }
    while(curP != NULL){
        cout<< curP->student->getID()<<","<<curP->student->getCredits()<<","<<curP->student->getGPA()<< endl;
        curP = curP->next;
    }
}
