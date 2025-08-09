import './App.css';
import {useState} from 'react';

const myurl = "https://reactjs.org/logo-og.png";
const user = {
  name: "Name",
  imageUrl: myurl,
  imageSize: 90,
};



function Button({Count, onClick}) {
  return(
    <div>
      <button onClick = {onClick}>
        按钮被点击了 {Count} 次
      </button>
    </div>
  );
}

const products = [
  {title: "Cabbage", id: 1},
  {title: "Garlic", id: 2},
  {title: "Apple", id: 3},
];

const listItems = products.map((products) =>
  <li key = {products.id}
        style = {{color: "darkgreen", fontSize: "20px"}}>
    {products.title}
  </li>
)
/*map()函数的参数是处理每个元素的回调函数*/

function App() {
  const [Count, setCount] = useState(0);
  function handle_Click() {
    setCount(Count + 1);
    alert("按钮被点击了");
  }
  return (
    <div>
      <h1>欢迎来到我的React应用</h1>
      <Button Count={Count} onClick={handle_Click} />
      <Button Count={Count} onClick={handle_Click} />
      <ul>{listItems}</ul>
    </div>
  );
}

export default App;
// function App() {
//   return (
//     <div>
//       <h2>欢迎来到我的React应用</h2>
//       <Button />
//       <>
//         <h3>
//           {user.name}
//         </h3>
//         <img className = "avatar"
//           src={user.imageUrl}
//           alt={user.name}
//           style={{ width: user.imageSize, height: user.imageSize }}
//         />
//       </>
//     </div>
//   );
// }