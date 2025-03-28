# String Dictionary

## Needed components
* [String Operations](https://github.com/Bejmach/StringOperations)

## Comparison of string dictionaries that are supported by this component
### Comparison made using chrono in cpp
* list - vector
* UM - unordered list
* BTree - binary tree
---
**creation time - list size: 1000**

BTree: 1846μs -> 0.001846sec  
List: 1202μs -> 0.001202sec  
UM: 1345μs -> 0.001345sec  
List: 1.0 times faster that list  
Unordered map: 0.89368 times faster than list  
BTree: 0.651138 times faster than list

---
---
**list size: 1000; repetitions: 1; total iterations: 1000**

BTree: 167μs -> 0.000167sec  
List: 93133μs -> 0.093133sec  
UM: 34992μs -> 0.034992sec  
List: 1.0 times faster that list  
Unordered map: 2.66155 times faster than list  
BTree: 557.683 times faster than list

---
---
**list size: 1000; repetitions: 26; total iterations: 26000**

BTree: 3049μs -> 0.003049sec  
List: 2411533μs -> 2.411533sec  
UM: 911635μs -> 0.911635sec  
List: 1.0 times faster that list  
Unordered map: 2.64528 times faster than list  
BTree: 790.926 times faster than list

---
---
**list size: 1000; repetitions: 51; total iterations: 51000**

BTree: 5894μs -> 0.005894sec  
List: 4751591μs -> 4.751591sec  
UM: 1795212μs -> 1.795212sec  
List: 1.0 times faster that list  
Unordered map: 2.64681 times faster than list  
BTree: 806.174 times faster than list

---
---
**list size: 1000; repetitions: 76; total iterations: 76000**

BTree: 9080μs -> 0.009080sec  
List: 7116220μs -> 7.116220sec  
UM: 2674308μs -> 2.674308sec  
List: 1.0 times faster that list  
Unordered map: 2.66096 times faster than list  
BTree: 783.725 times faster than list

---
---
**list size: 1000; repetitions: 101; total iterations: 101000**

BTree: 11930μs -> 0.011930sec  
List: 9366917μs -> 9.366917sec  
UM: 3562310μs -> 3.562310sec  
List: 1.0 times faster that list  
Unordered map: 2.62945 times faster than list  
BTree: 785.156 times faster than list

---
