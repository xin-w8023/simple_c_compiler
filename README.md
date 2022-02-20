### How to build the toy
```shell
mkdir build
cd build
cmake ../
make -j 4
cd ..
./build/scc example/main.scc
```

### the output will be an ast syntax tree like following.
```markdown
[=]:Assignment Expression
|  [x]:Variable
|  [+]:Plus Expression
|  |  [y]:Variable
|  |  [*]:Star Expression
|  |  |  [/]:Slash Expression
|  |  |  |  [*]:Star Expression
|  |  |  |  |  [2]:Constant
|  |  |  |  |  [3]:Constant
|  |  |  |  [+]:Plus Expression
|  |  |  |  |  [2]:Constant
|  |  |  |  |  [4]:Constant
|  |  |  [1]:Constant
```
