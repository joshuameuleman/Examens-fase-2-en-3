import { useState, useRef } from "react";

function Counter() {
    const [value, setValue] = useState(0);
    const valueRef = useRef(0);

    function incrValue() {
        setValue(value + 1);
    }

    function incrRef() {
        valueRef.current += 1;
    }

    return (
        <>
            <button onClick={incrValue}>value + 1</button>
            &nbsp;=&gt;
            value = {value};
            &nbsp;&nbsp;
            <button onClick={incrRef}>ref + 1</button>
            &nbsp;=&gt;
            ref = {valueRef.current};
            &nbsp;&nbsp;
        </>
    )
}

export default Counter;