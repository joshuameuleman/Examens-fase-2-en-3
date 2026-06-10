import logo from './logo.svg';
import './App.css';
import Countries from "./Countries.js";
import { useState } from "react";

function App() {
  const [name, setName] = useState("");

  function change(event) {
    const value = event.target.value;
    setName(value);
  }

  return (
    <>
      Country: <input type="text" onChange={change} /> <br /><br />
      <Countries name={name} />
    </>
  )
}

export default App;