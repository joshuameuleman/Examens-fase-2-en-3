import { useState, useEffect } from "react";
import style from './Counter.module.css';

function Counter(props) {
    const init = parseInt(props.init || 0);
    const end = parseInt(props.end || 0);
    const [count, setCount] = useState(init);

    useEffect(function () {
        //if (end && count >= end) return;
        if (end != 0 && count >= end) return;

        const timer = setInterval(function () {
            setCount((count) => count + 1);
            console.log("count =", count);
        }, 1000);

        return function () {
            clearInterval(timer);
        }
    });

    return (
        <>
            Initial value of the counter is: {init}
            <br />
            End of the counter at: {end}
            <br />
            The counter is: {count}
            <br />
            {
                (end != 0 && count >= end) ? <b className={style.stopped}>Counter stopped</b>
                    : <i>Counter in progress</i>
            }
        </>
    )
}

export default Counter;