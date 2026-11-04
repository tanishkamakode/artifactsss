// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudentData{
    struct Student{
        uint id;
        string name;
        uint age;
    }

    Student[] private students;

    function addStudent(string memory nameee, uint ageee) public{
        uint iddd = students.length;
        students.push(Student(iddd, nameee, ageee));
    }

    function getStudent(uint iddd) public view returns(uint, string memory, uint){
        require(students.length > iddd, "Student doesn't exist");
        Student memory student = students[iddd];
        return (student.id, student.name, student.age);
    }

    function getCount() public view returns(uint){
        return students.length;
    }
}