import { useState, useEffect } from "react";

function Counter(props) {
    const init = parseInt(props.init || 0);
    const [count, setCount] = useState(init);

    useEffect(function () {
        const timer = setInterval(function () {
            setCount((count) => count + 1);
        }, 1000);
        return function () {
            clearInterval(timer);
        }
    });

    return (
        <>
            Initial value of the counter is: {init}
            <br />
            The counter is: {count}
        </>
    )
}

export default Counter;
