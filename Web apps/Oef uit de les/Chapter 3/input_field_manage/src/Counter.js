import { useState } from "react";

function Counter() {
    const [value, setValue] = useState("");
    
    function change(event) {
        setValue(event.target.value);
    }

    return (
        <>
            Counter : <input type="text" onChange={change} /> <br />
            <br />
            Input Value : {value}
        </>
    )
}

export default Counter;