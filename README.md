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
```markdown
[=]:Assignment BiExpression
|  [x]:Variable
|  [+]:Plus BiExpression
|  |  [-]:Negative UnExpression
|  |  |  [y]:Variable
|  |  [*]:Star BiExpression
|  |  |  [/]:Slash BiExpression
|  |  |  |  [*]:Star BiExpression
|  |  |  |  |  [2]:Constant
|  |  |  |  |  [3]:Constant
|  |  |  |  [+]:Plus BiExpression
|  |  |  |  |  [2]:Constant
|  |  |  |  |  [4]:Constant
|  |  |  [1]:Constant
```
