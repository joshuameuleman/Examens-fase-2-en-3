import { useContext, useState } from "react";
import { TotalContext } from "./App";

// 1) en 3)
function Counter() {

    // 2) functie setTotal doorgeven
    //function Counter({ setTotal }) {

    const [value, setValue] = useState(0);

    // 3)
    //const [total, setTotal] = useContext(TotalContext);

    function incrValue() {
        setValue(value + 1);

        // 2) en 3)
        //setTotal((total) => total + 1);
    }

    return (
        <>
            <button onClick={incrValue}>value + 1</button>
            &nbsp;=&gt;
            value = {value};
            &nbsp;&nbsp;
        </>
    )
}

export default Counter;