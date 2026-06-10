import { useState, useEffect } from "react";
import { Text } from "react-native";

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
        <Text>The counter is set to: {count}</Text>
    )
}

export default Counter;