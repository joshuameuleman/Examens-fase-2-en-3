import { useState, createContext } from "react";
import logo from './logo.svg';
import './App.css';
import Counter from "./Counter.js";
import React from "react";

// 3)
//const TotalContext = createContext();

function App() {
  const [total, setTotal] = useState(0);

  return (
    // 1) init: hoe totaal updaten?
    <>
      Counter#1 : <Counter />
      <hr style={{ margin: '10px', height: '3px', backgroundColor: 'gray'}} />
      Counter#2 : <Counter />

      <hr style={{ margin: '10px', height: '3px', backgroundColor: 'gray' }} />
      <b>Total value = {total}</b>
    </>

    // 2) functie setTotal als attribuut doorgeven aan Counter
    /*
    <>
      Counter#1 : <Counter setTotal={setTotal} />
      <hr style={{ margin: '10px', height: '3px', backgroundColor: 'gray'}} />
      Counter#2 : <Counter setTotal={setTotal} />

      <hr style={{ margin: '10px', height: '3px', backgroundColor: 'gray' }} />
      <b>Total value = {total}</b>
    </>
    */

    // 3) 
    /*
    <>
      <TotalContext.Provider value={[total, setTotal]}>
        Counter#1 : <Counter />
        <hr style={{ margin: '10px', height: '3px', backgroundColor: 'gray' }} />
        Counter#2 : <Counter />
        <hr style={{ margin: '10px', height: '3px', backgroundColor: 'gray' }} />

        <b>Total value = {total}</b>
      </TotalContext.Provider>
    </>
    */
  )
}

// 1) en 2)
export default App;

// 3)
//export { App, TotalContext };