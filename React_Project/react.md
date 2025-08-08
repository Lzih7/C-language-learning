## react的核心逻辑
1. 组件化，组件名称首字母要大写，与html区分
2. 与css结合，用`className`来指定css里的`class`
## 箭头函数 (=>)
- => 是箭头函数（Arrow Function）的语法，是 ES6（ECMAScript 2015）引入的一种简洁的函数定义方式。

例如：
```js
const handleChange = (e) => { // e是函数的参数
  // 函数体
};
```
箭头函数与传统的 function 声明相比，语法更简洁，并且不会绑定自己的 this，常用于 React 组件和回调函数中。
## useState
useState是 React 提供的一个 Hook，用于在函数组件中声明和管理状态变量。它的作用是让你可以在组件内部保存和更新数据（比如表单内容、计数器等），并在数据变化时自动重新渲染组件。

用法示例：

`const [count, setCount] = useState(0);`

- count 是当前的状态值（初始值为 0）
- setCount 是用来更新 count 的函数。
- 在代码里，useState 用于管理表单数据、错误信息、提交状态等。