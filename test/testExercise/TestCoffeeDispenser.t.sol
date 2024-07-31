// SPDX-License-Identfier: MIT
pragma solidity ^0.8.19;

import {Test} from "lib/forge-std/src/Test.sol";
import {CoffeeDispenser} from "src/exercise/coffeeDispenser.sol";

contract testCoffeeDispenser is Test {
    CoffeeDispenser coffeeDispenser;
    address public owner;

    function setUp() public {
        owner = address(this);
        vm.prank(owner);
        coffeeDispenser = new CoffeeDispenser();
    }

    function testCheckCoffeeSupply() public view {
        uint initialCoffeeSupply = coffeeDispenser.checkCoffeeSupply();
        assertEq(initialCoffeeSupply, 100);
    }

    function testAddCoffee(uint amount) public {
        amount = 5;
        vm.prank(owner);

        coffeeDispenser.addCoffee(amount);

        assertEq(coffeeDispenser.checkCoffeeSupply(), 105);
    }

    function testBuyCoffeeSuccess(uint amount) public {
        amount = 5;
        uint256 cost = amount * coffeeDispenser.COFFEE_PRICE();

        coffeeDispenser.buyCoffee{value: cost}(amount);

        assertEq(coffeeDispenser.numberOfCoffee(), 95);
    }

    function testBuyCoffeeInvalidAmount() public {
        uint256 cost = coffeeDispenser.COFFEE_PRICE();

        vm.expectRevert("invalid number of coffee");
        coffeeDispenser.buyCoffee{value: cost}(0);
    }

    function testBuyCoffeeInsufficientSupply() public {
        vm.expectRevert("not enough coffee");
        coffeeDispenser.buyCoffee{value: 101 * 5 ether}(101);
    }

    function testBuyCoffeeInsufficentPayment() public {
        uint256 amount = 5;
        uint256 insufficientPayment = amount *
            coffeeDispenser.COFFEE_PRICE() -
            1;

        vm.expectRevert("insufficient balance");
        coffeeDispenser.buyCoffee{value: insufficientPayment}(amount);
    }

    receive() external payable {}
}
