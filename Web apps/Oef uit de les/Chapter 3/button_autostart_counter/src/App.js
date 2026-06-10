import logo from './logo.svg';
import './App.css';
import Counter from "./Counter.js";
import React from "react";

function App() {
  return (
    <>
      {
        [...Array(3).keys()].map(function (i) {
          const val = i < 2 ? '1' : '0'; // Value of the "autostart" attribute
          return (
            <React.Fragment key={i}>
              Counter {i} defined by {`<Counter autostart='${val}' init='5' end='${10 + i}' />`} : <br />
              <Counter autostart={val} init='5' end={10 + i} />
              <br /><br />
            </React.Fragment>
          )
        })
      }
    </>
  )
}

export default App;