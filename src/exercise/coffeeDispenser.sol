// SPDX-License-Identifier: MIT
pragma solidity ^0.8.19;

contract CoffeeDispenser {
    address owner;
    uint256 public numberOfCoffee = 100;
    uint256 public constant COFFEE_PRICE = 0.1 ether;

    constructor() {
        owner = msg.sender;
    }

    function checkCoffeeSupply() public view returns (uint256) {
        return numberOfCoffee;
    }

    function addCoffee(uint amount) public {
        require(msg.sender == owner, "Not authorized address");
        numberOfCoffee += amount;
    }

    function buyCoffee(uint amount) public payable {
        require(amount > 0, "invalid number of coffee");
        require(amount <= numberOfCoffee, "not enough coffee");

        uint cost = amount * COFFEE_PRICE;
        require(msg.value >= cost, "insufficient balance");

        numberOfCoffee -= amount;
    }
}
