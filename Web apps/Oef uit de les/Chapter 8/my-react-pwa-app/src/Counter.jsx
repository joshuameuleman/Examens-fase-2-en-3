import { useState, useEffect } from "react";

function Counter() {
    const [count, setCount] = useState(0);

    useEffect(function () {
        const timer = setInterval(function () {
            setCount((count) => count + 1);
        }, 1000);
        return function () {
            clearInterval(timer);
        }
    }, []);
    
    return (
        <>
            The counter is set to: {count}
        </>
    )
}

export default Counter;