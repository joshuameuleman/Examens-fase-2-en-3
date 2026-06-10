import logo from './logo.svg';
import './App.css';
import Counter from "./Counter.js";
import React from 'react';

function App() {
  return (
    <>
      {
        // 1a) using an self-invoked function
        (function () {
          const jsx = [];

          for (let i = 0; i < 3; i++) {
            jsx.push(
              <>
                Counter {i} defined by {`<Counter init='5' end='${10 + i}' />`} : <br />
                <Counter init='5' end={10 + i} />
                <br /><br />
              </>
            );
          }

          return jsx;
        })()
      }

      {
        /*
        //1b) small optimization of 1a) using key attribute makes React able to handle lists more efficiently
        (function () {
          const jsx = [];

          for (let i = 0; i < 3; i++) {
            jsx.push(
              <React.Fragment key={i}>
                Counter {i} defined by {`<Counter init='5' end='${10 + i}' />`} : <br />
                <Counter init='5' end={10 + i} />
                <br /><br />
              </React.Fragment>
            );
          }

          return jsx;
        })()
        */
      }

      {
        //2) using map() of JavaScript array class
        /*[0, 1, 2].map(function (i) {
          return (
            <React.Fragment key={i}>
              Counter {i} defined by {`<Counter init='5' end='${10 + i}' />`} : <br />
              <Counter init='5' end={10 + i} />
              <br /><br />
            </React.Fragment>
          )
        })*/
      }
    </>
  );
}

export default App;
