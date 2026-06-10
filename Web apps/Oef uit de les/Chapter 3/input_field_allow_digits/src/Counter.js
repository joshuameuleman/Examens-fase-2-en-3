import { useState } from "react";

function Counter() {
    const [value, setValue] = useState("");

    function change(event) {
        setValue(event.target.value);
    }

    function keydown(event) {
        // Display the pressed key in the console
        console.log(event.key);
        // Allow the Backspace, Delete, ArrowLeft, ArrowRight, and Tab keys
        if (["Backspace", "Delete", "ArrowLeft", "ArrowRight", "Tab"].includes(event.key)) return;
        // Then disallow all other keys except those from 0 to 9
        if (event.key < "0" || event.key > "9") event.preventDefault();
    }
    
    return (
        <>
            Counter : <input type="text" onChange={change} onKeyDown={keydown} /> <br /><br />
            Input Value : {value}
        </>
    )
}

export default Counter;