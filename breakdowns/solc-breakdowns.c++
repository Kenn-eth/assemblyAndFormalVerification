   // 0x6080604052348015600e575f80fd5b5060a580601a5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c80637ce176d4146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea2646970667358221220f89e89a08ca2f43b672584309585914865373dfc35a58788b936cc58fe26d38864736f6c634300081a0033

// There are three sections of this bytecode
1. Contract creation
2. Runtime
3. Metadatata

// 1. Contract Creation
// Free memory pointer (0x40)
PUSH1 0x80              // [0x80]
PUSH1 0x40              // [0x40]
MSTORE                  // []   Memory 0x40 -> 0x80 Points to free memory(0x80 is free)

// What does this chunk do
// Checks if someone sent some value. Jumps if there is no value sent
CALLVALUE               // [msg.value]
DUP1                    // [msg.value, msg.value]
ISZERO                  // [msg.value == 0, msg.value] comparism check if value is 0; returns 0 if the value is not 0, and 1 if the value is 0
PUSH1 0x0e              // [0x0e, msg.value == 0, msg.value] 0x0e is the program counter
JUMPI                   // [msg.value] checks if value is 0, then jumps, otherwise move on
PUSH0                   // [0x00, msg.value]
DUP1                    // [0x00, 0x00, msg.value]
REVERT                  // [msg.value] the code reverts if there is value sent; the contract is not payable

// jumpdest if msg.value == 0
JUMPDEST                // [msg.value]
POP                     // []
PUSH1 0xa5              // [0xa5]
DUP1                    // [0xa5, 0xa5]
PUSH1 0x1a              // [0x1a, 0xa5, 0xa5]
PUSH0                   // [0x00, 0x1a, 0xa5, 0xa5]
CODECOPY                // [0xa5] copy code running in current environment to memory
PUSH0                   // [0x00, 0xa5]
RETURN                  // []
INVALID                 // []

// 2. Runtime Code
// Free memory pointer
PUSH1 0x80              // [0x80]
PUSH1 0x40              // [0x40]
MSTORE                  // []   Memory 0x40 -> 0x80 Points to free memory(0x80 is free)

CALLVALUE               // [msg.value]
DUP1                    // [msg.value, msg.value]
ISZERO                  // [msg.value == 0, msg.value]
PUSH1 0x0e              // [0x0e, msg.value == 0, msg.value]
JUMPI                   // [msg.value] checks if value is 0, then jumps, otherwise move on
PUSH0                   // [0, msg.value]
DUP1                    // [0, 0, msg.value]
REVERT                  // [msg.value] reverts if there is value sent

// starts here if msg.value == 0
// this code section checks if calldata has function selector. then jumps to it. 
JUMPDEST                // [msg.value]
POP                     // []
PUSH1 0x04              // [0x04]
CALLDATASIZE            // [calldataszie, 0x04] checks the size of data in the current environment
LT                      // [calldatasize < 0x04] less than comparism btw a and b. checking if calldatasize is less than 0x04 bytes
PUSH1 0x30              // [0x30, calldatasize < 0x04]
JUMPI                   // [] jumps if comparism is true. 0x30 is the program counter

// Code section is Function Dispatching
PUSH0                   // [0x00]
CALLDATALOAD            // [calldata_32bytes]
PUSH1 0xe0              // [0xe0, calldata_32bytes]
SHR                     // [func_sel] right bitwise shift of 0xe0(224 bits)
DUP1                    // [func_sel, func_sel]
PUSH4 0x7ce176d4        // [0x7ce176d4, func_sel, func_sel]
EQ                      // [func_sel == 0x7ce176d4, func_sel] compares the two func_sel on top of the stack
PUSH1 0x34              // [0x34, func_sel == 0x7ce176d4, func_sel]
JUMPI                   // [func_sel] jumps if comparism is true; 0x34 is the program counter

// Another function Dispatching for readNumberOfHorses
DUP1                    // [func_sel, func_sel]
PUSH4 0xe026c017        // [0xe026c017, func_sel, func_sel]
EQ                      // [func_sel == 0xe026c017, func_sel]
PUSH1 0x45              // [0x45, func_sel == 0xe026c017, func_sel]
JUMPI                   // [func_sel]

// calldata jump. if none of the EQ comaparison gets true, code will not jump and eventually reverts
JUMPDEST                // []
PUSH0                   // [0x00]
DUP1                    // [0x00, 0x00]
REVERT                  // []

// calldata jump: updateNumOfHorses jumpdest 1
JUMPDEST                // [func_sel]
PUSH1 0x43              // [0x43, func_sel]
PUSH1 0x3f              // [0x3f, 0x43, func_sel]
CALLDATASIZE            // [calldatasize, 0x3f, 0x43, func_sel]   
PUSH1 0x04              // [0x04, calldatasize, 0x3f, 0x43, func_sel]
PUSH1 0x59              // [0x59, 0x04, calldatasize, 0x3f, 0x43, func_sel]
JUMP                    // [0x04, calldatasize, 0x3f, 0x43, func_sel]

// UpdateNumOfHorses jumpdest 4 (jumping from jumpdest 3)
JUMPDEST                // [calldata, 0x43, func_sel]
PUSH0                   // [0, calldata, 0x43, func_sel]
SSTORE                  // [0, calldata, 0x43, func_sel] storage[0] -> [calldata]
JUMP                    // [func_sel]

// jump dest 5
JUMPDEST                // [func_sel]
STOP                    // end execution

// jumpdest for readNumberOfHorses
JUMPDEST               // [func_sel]
PUSH0                  // [0, func_sel]   
SLOAD                  // [numOfHorses, func_sel]
PUSH1 0x40             // [0x40, numOfHorses, func_sel]
MLOAD                  // [0x80, numOfHorses, func_sel] Memory 0x40 -> 0x80 (free memory pointer)
SWAP1                  // [numOfHorses, 0x80, func_sel]
DUP2                   // [0x80, numOfHorses, 0x80, func_sel]
MSTORE                 // [0x80, func_sel] memory: 0x80 -> numOfHorses
PUSH1 0x20             // [0x20, 0x80, func_sel]
ADD                    // [0xa0, 0x80, func_sel]
PUSH1 0x40             // [0x40, 0xa0, func_sel]
MLOAD                  // [0x80, 0xa0, func_sel]
DUP1                   // [0x80, 0x80, 0xa0, func_sel]
SWAP2                  // [0xa0, 0x80, 0x80, func_sel]
SUB                    // [0x20, 0x80, func_sel]
SWAP1                  // [0x80, 0x20, func_sel]
RETURN                 // [func_sel] returns a value of size 0x20 located at position 0x80 in memory

// UpdateNumOfHorses jumpdest 2
JUMPDEST                     // [0x04, calldatasize, 0x3f, 0x43, func_sel]
PUSH0                        // [0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]
PUSH1 0x20                   // [0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]
DUP3                         // [0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]
DUP5                         // [calldatasize, 0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]
SUB                          // [calldatasize - 0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]
// comparism to check if calldata_size is more than the function selector + 0x20
SLT                          // [calldatasize - 0x04 < 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]
ISZERO                       // [more_calldata_than_sel?, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]
PUSH1 0x68                   // [0x68, more_calldata_than_sel?, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]
JUMPI                        // [0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel] jump if there is more calldata than func_sel + 0x20

// revert otherwise
PUSH0                        // [0x00, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]
DUP1                         // [0x00, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]
REVERT                       // [0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]

// UpdateNumOfHorses jumpdest 3
JUMPDEST                     // [0x00, 0x04, calldatasize, 0x3f, 0x43, func_sel]
POP                          // [0x04, calldatasize, 0x3f, 0x43, func_sel]
CALLDATALOAD                 // [calldata, calldatasize, 0x3f, 0x43, func_sel
SWAP2                        // [0x3f, calldatasize, calldata, 0x43, func_sel] 
SWAP1                        // [calldatasize, 0x3f, calldata, 0x43, func_sel]
POP                          // [calldatasize, 0x3f, calldata, 0x43, func_sel]
JUMP                         // [0x3f, calldata, 0x43, func_sel]

// 3. Metadata
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
INVALID
SWAP15
DUP10
LOG0
DUP13
LOG2
DELEGATECALL
EXTCODESIZE
PUSH8 0x2584309585914865
CALLDATACOPY
RETURNDATASIZE
INVALID
CALLDATALOAD
INVALID
DUP8
DUP9
INVALID
CALLDATASIZE
INVALID
PC
INVALID
INVALID
INVALID
DUP9
PUSH5 0x736f6c6343
STOP
ADDMOD
BYTE
STOP
CALLER