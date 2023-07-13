# Easy_Indicators

原始项目[来源🔗](https://github.com/AmyrAhmady/cpp-indicators)

原项目中更改一个bug

```c++
// 原代码，因为duration是一个引用，无法识别200ms。
auto spin = std::make_unique<indicator::indicator>(200ms, 3, "Finished loading some data", "Process info: ", " Loading data...");
// 转换
auto spin = std::make_unique<indicator::indicator>(std::chrono::milliseconds(200), 3, "Finished loading some data", "Process info: ", " Loading data...");
```

还有一个地方就是对于时间截止时，无法将状态静止到最后一个。

做这个项目的原因是作为看源码 [p-ranav/indicators](https://github.com/p-ranav/indicators) 的前要，easy版本