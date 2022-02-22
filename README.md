### How to build the toy
```shell
mkdir build
cd build
cmake ../
make -j 4
cd ..
./build/scc example/main.scc
```

### the output will be an abstract syntax tree like following.
```text
BinaryExpression
*  [x]: Variable
*  [=]: Assignment
*  BinaryExpression
*  *  UnaryExpression
*  *  *  [-]: Negative
*  *  *  [y]: Variable
*  *  [+]: Plus
*  *  BinaryExpression
*  *  *  BinaryExpression
*  *  *  *  BinaryExpression
*  *  *  *  *  [2]: Constant
*  *  *  *  *  [*]: Star
*  *  *  *  *  [3]: Constant
*  *  *  *  [/]: Slash
*  *  *  *  BinaryExpression
*  *  *  *  *  [2]: Constant
*  *  *  *  *  [+]: Plus
*  *  *  *  *  [4]: Constant
*  *  *  [*]: Star
*  *  *  [1]: Constant
```
