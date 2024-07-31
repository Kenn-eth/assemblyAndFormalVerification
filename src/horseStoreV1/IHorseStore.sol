//SPDX-License-Identifier: MIT
pragma solidity ^0.8.19;

interface IHorseStore {
    function updateNumOfHorses(uint newNumOfHorses) external;
    function readNumberOfHorses() external view returns (uint256);
}
