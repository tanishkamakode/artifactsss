// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract BankAccount{
    mapping(address => uint) private balances;
    event Deposited(address indexed user, uint amount);
    event Withdrawn(address indexed user, uint amount);

    function deposit() public payable{
        require(msg.value > 0, "Amount should be greater than 0");
        balances[msg.sender] += msg.value;
        emit Deposited(msg.sender, msg.value);
    }

    function withdraw(uint amount) public{
        require(amount > 0 && balances[msg.sender] >= amount, "Insufficient Balance");
        balances[msg.sender] -= amount;
        (bool success, ) = payable(msg.sender).call{value: amount}("");
        require(success, "Transfer failed");
        emit Withdrawn(msg.sender, amount);
    }

    function showBalance() public view returns(uint){
        return balances[msg.sender];
    }
}