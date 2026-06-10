import logo from './logo.svg';
import './App.css';
import Counter from "./Counter.js";
import React from 'react';

function App() {
  return (
    <>
      {
        [0, 1, 2].map(function (i) {
          return (
            <React.Fragment key={i}>
              Counter {i} defined by {`<Counter init='5' end='${10 + i}' />`} : <br />
              <Counter init='5' end={10 + i} />
              <br /><br />
            </React.Fragment>
          )
        })
      }
    </>
  );
}

export default App;
