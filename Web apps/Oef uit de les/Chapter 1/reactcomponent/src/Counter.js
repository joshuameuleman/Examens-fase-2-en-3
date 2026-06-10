import { useState, useEffect } from "react";

function Counter() {
    //1)
    let count = 0;

    setInterval(function () {
        count++;
        console.log("count =", count);
    }, 1000);

    //2)
    /*
    const [count, setCount] = useState(0);

    setInterval(function () {
        setCount(count + 1);
        console.log("count =", count);
    }, 1000);
    */
    
    //3)
    /*
    const [count, setCount] = useState(0);
    
    useEffect(function () {
        const timer = setInterval(function () {
            //4)
            setCount(count + 1);
            //setCount(count + 1);

            //5)
            //setCount((count) => count + 1);
            //setCount((count) => count + 1);
            //console.log("count =", count);
        }, 1000);
        return function () {
            clearInterval(timer);
        }
    });
    */

    return (
        <>
            The counter is set to: {count}
        </>
    )
}

export default Counter;