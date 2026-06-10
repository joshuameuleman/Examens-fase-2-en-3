import logo from './logo.svg';
import './App.css';
import Counter from "./Counter.js";

function App() {
  return (
    <>
      Counter#1 : <Counter name="Counter#1" />
      <hr style={{ margin: '10px', height: '3px', backgroundColor: 'gray' }} />
      Counter#2 : <Counter name="Counter#2" />
    </>
  )
}

export default App;