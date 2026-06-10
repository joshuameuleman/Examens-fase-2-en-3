import logo from './logo.svg';
import './App.css';
import Counter from "./Counter.js";
import useForceUpdate from "./useForceUpdate";

function App() {
  const forceUpdate = useForceUpdate();

  function refresh() {
    forceUpdate();
  }

  return (
    <>
      Counter#1 : <Counter />
      <hr style={{ margin: '10px', height: '3px', backgroundColor: 'gray' }} />
      Counter#2 : <Counter />
      <br /><br />
      <button onClick={refresh}>Refresh</button>
    </>
  )
}

export default App;