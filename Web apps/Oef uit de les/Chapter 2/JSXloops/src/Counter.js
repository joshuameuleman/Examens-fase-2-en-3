import { useState, useEffect } from "react";

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
                // 1) using an self-invoked JavaScript function
                (function () {
                    //if (end && count >= end) return <b>Counter stopped</b>;
                    if (end != 0 && count >= end) return <b>Counter stopped</b>;
                    else return <i>Counter in progress</i>;
                })()
            }
            {
                // 2) using JavaScript ternary operator
                //(end != 0 && count >= end) ? <b>Counter stopped</b> : <i>Counter in progress</i>
            }
        </>
    )
}

export default Counter;