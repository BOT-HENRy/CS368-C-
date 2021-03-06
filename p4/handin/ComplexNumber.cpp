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
 * Assignment:    Programming Assignment 4
 ******************************************************************************/
 
#include <iostream>
#include "ComplexNumber.h"

using namespace std;

// constructors
ComplexNumber::ComplexNumber(){
  real = 0;      
  imag = 0;
}

ComplexNumber::ComplexNumber(double real_part, double imaginary_part){
  real = real_part;
  imag = imaginary_part;
}

ComplexNumber::ComplexNumber(const ComplexNumber & rhs){
  real = rhs.real;
  imag = rhs.imag;
}

// named member functions
void ComplexNumber:: print(ostream & out) const{
  if(imag < 0){
    cout << real <<" - "<< -imag << "i";
  }else{
    cout << real <<" + "<< imag << "i";
  }
}

bool ComplexNumber:: equals(const ComplexNumber & rhs) const{
  if((real == rhs.real)&&(imag == rhs.imag)){
    return true;
  }else{
    return false;
  }
}

// assignment operators
const ComplexNumber & ComplexNumber:: operator=(const ComplexNumber & rhs){
  real = rhs.real;
  imag = rhs.imag;
}

const ComplexNumber & ComplexNumber:: operator+=(const ComplexNumber & rhs){
  real = real + rhs.real;
  imag = imag + rhs.imag;
}

const ComplexNumber & ComplexNumber:: operator-=(const ComplexNumber & rhs){
  real = real - rhs.real;
  imag = imag - rhs.imag;
}

const ComplexNumber & ComplexNumber:: operator*=(const ComplexNumber & rhs){
  double currR = real; //get a copy of original real number
  real = real * rhs.real - imag * rhs.imag;
  imag = currR * rhs.imag + imag * rhs.real;
}

// arithmetic operators
ComplexNumber operator+(const ComplexNumber & lhs, const ComplexNumber & rhs){
  ComplexNumber curr = ComplexNumber(lhs);  
  curr += rhs;
  return curr;
}

ComplexNumber operator-(const ComplexNumber & lhs, const ComplexNumber & rhs){
  ComplexNumber curr = ComplexNumber(lhs);  
  curr -= rhs;
  return curr;
}
ComplexNumber operator*(const ComplexNumber & lhs, const ComplexNumber & rhs){
  ComplexNumber curr = ComplexNumber(lhs);  
  curr *= rhs;
  return curr;
}

// relational operators
bool operator==(const ComplexNumber & lhs, const ComplexNumber & rhs){
  if(lhs.equals(rhs)){
    return true;
  }else{
    return false;
  }
}

bool operator!=(const ComplexNumber & lhs, const ComplexNumber & rhs){
  if(!lhs.equals(rhs)){
    return true;
  }else{
    return false;
  }
}

// I/O operators
ostream & operator<<(ostream & out, const ComplexNumber & n){
  n.print();
  out << "";
  return out;
}
istream & operator>>(istream & in, ComplexNumber & n){
  double real_part;
  in >> real_part;
  char s;  //for the sign
  in >> s;
  double imaginary_part;
  in >> imaginary_part;
  if(s == '-'){
    imaginary_part = 0 - imaginary_part;  //if negative
  }else{
    imaginary_part = imaginary_part;
  }
  char i;
  in >> i;
  n = ComplexNumber(real_part, imaginary_part);
  return in;
}






