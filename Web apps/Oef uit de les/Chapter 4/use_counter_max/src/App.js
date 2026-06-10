import logo from './logo.svg';
import './App.css';
import Counter from "./Counter.js";

function App() {
  return (
    <>
      Counter#1 : <Counter />
      <hr style={{ margin: '10px', height: '3px', backgroundColor: 'gray' }} />
      Counter#2 : <Counter max={10} />
    </>
  )
}

export default App;