// SPDX-License-Identifier: MIT

pragma solidity ^0.8.19;

contract HorseStore {
    uint256 numberOfHorses;

    function updateNumOfHorses(uint256 newNumberOfHorses) external {
        numberOfHorses = newNumberOfHorses;
    }

    function readNumberOfHorses() external view returns (uint256) {
        return numberOfHorses;
    }
}
