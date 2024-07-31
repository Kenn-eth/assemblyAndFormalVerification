object "HorseStoreYul" {
    code {
        // contract deployment
        datacopy(0, dataoffset("runtime"), datasize("runtime"))
        return(0, datasize("runtime"))
    }

    object "runtime" {
        code {
            // function dispatching
            switch selector()

            // updateNumOfHorses: 0x7ce176d4 
            case 0x7ce176d4 {
                storeNumber(decodeAsUint(0))
            }

            // readNumberOfHorses: 0xe026c017
            case 0xe026c017 {
                returnUint(readNumber())
            }

            default {
                revert(0,0)
            }

            function storeNumber(newNumber) {
                sstore(0, newNumber)
            }

            function readNumber() -> storedNumber {
                storedNumber := sload(0)
            }

            /* decoding functions */
            function selector() -> x {
                s := div(calldataload(0), 0x100000000000000000000000000000000000000000000000000000000)
            }

            function decodeAsUint(offset) -> v {
                let positionInCalldata := add(4, mul(offset, 0x20))
                if lt(calldatasize(), add(positionInCalldata, 0x20)) {
                    revert (0,0)
                }

                v := calldataload(positionInCalldata)
            }

            function returnUint(v) {
                mstore(0, v)
                return (0, 0x20)
            }
        }
    }
}