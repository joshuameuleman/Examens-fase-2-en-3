import logo from './logo.svg';
import './App.css';
import Counter from "./Counter.js";

function App() {
  return (
    <>
      { /* JSX code of the components returned by the component */}
      Counter defined by {"<Counter init='5' end='10' />"} : <br />
      <Counter init='5' end='10' />
      <br /> <br />

      Counter defined by {"<Counter init={5} end={15} />"} : <br />
      <Counter init={5} end={15} />
      <br /> <br />

      Counter defined by {"<Counter />"} : <br />
      <Counter />
      <br />
    </>
  );
}

export default App;
