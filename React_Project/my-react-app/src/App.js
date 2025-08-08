import './App.css';
import {useState} from 'react';

const myurl = "https://reactjs.org/logo-og.png";
const user = {
  name: "Name",
  imageUrl: myurl,
  imageSize: 90,
};



function Button() {
  const [Count, setCount] = useState(0);
  function handle_Click() {
    setCount(Count + 1);
    alert("按钮被点击了");
  }
  return(
    <div>
      <button onClick = {handle_Click}>
        这是一个按钮
      </button>
      <p className="Count_text">按钮被点击了 {Count} 次</p>
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
function App() {
  return (
    <div>
      <h2>欢迎来到我的React应用</h2>
      <Button />
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