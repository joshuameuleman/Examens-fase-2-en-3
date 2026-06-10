import { useState, useRef } from "react";
import usePreviousState from "./usePreviousState";
import useForceUpdate from "./useForceUpdate";

function Counter() {
    const [value, setValue] = useState(""); // Current content of the input field
    const prevValue = usePreviousState(value); // Previous content of the input field

    // 2)
    //const forceUpdate = useForceUpdate();

    function change(event) {
        const value = event.target.value;
        setValue(value);
    }

    // 2)
    /*
    function keydown(event) {
        if (event.key == "Backspace" || event.key == "Delete") forceUpdate();
    }
    */

    return (
        // 1) Probleem: laatste backspace om veld volledig leeg te maken werkt niet bij previous value
        <>
            Current value : <input type="text" onChange={change} />
            <br />
            Previous value : {prevValue}
        </>

        // 2)
        /*
        <>
            Current Value : <input type="text" onChange={change} onKeyDown={keydown} /> <br />
            Previous value : {prevValue}
        </>
        */
    )
}

export default Counter;