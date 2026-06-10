import { useState, useReducer } from "react";

function Counter() {
    // 1) Gebruik van useState
    
    const [value, setValue] = useState(0);

    function incrValue() {
        setValue(value + 1);
    }

    function decrValue() {
        setValue(value - 1);
    }
    

    // 2) Gebruik van useReducer met value als single waarde
    /*
    const [value, dispatch] = useReducer(function (value, action) {
        if (action == "INCR") value += 1;
        if (action == "DECR") value -= 1;
        console.log(value);

        return value;
    }, 0);
    */


    // 3) Gebruik van useReducer met state als object
    /*
    const [state, dispatch] = useReducer(function (state, action) {
        if (action == "INCR") state.value += 1;
        if (action == "DECR") state.value -= 1;
        return { ...state }; // Definitely do not write return state; !!!
    }, { value: 0 });
    */


    // 2) en 3)
    /*
    function incrValue() {
        dispatch("INCR");
    }

    function decrValue() {
        dispatch("DECR");
    }
    */


    // 4) Gebruik van useReducer met state en action als object
    /*
    const [state, dispatch] = useReducer(function (state, action) {
        if (action.type == "INCR") state.value += 1;
        if (action.type == "DECR") state.value -= 1;
        return { ...state }; // Definitely do not write return state; !!!
    }, { value: 0 });

    function incrValue() {
        dispatch({ type: "INCR" });
    }

    function decrValue() {
        dispatch({ type: "DECR" });
    }
    */


    // 5) Gebruik van useReducer met state en action als object, dynamische stapgrootte
    /*
    const [state, dispatch] = useReducer(function (state, action) {
        if (action.type == "INCR") state.value += action.value;
        if (action.type == "DECR") state.value -= action.value;
        return { ...state }; // Definitely do not write return state; !!!
    }, { value: 0 });

    function incrValue() {
        dispatch({ type: "INCR", value: 10 });
    }

    function decrValue() {
        dispatch({ type: "DECR", value: 10 });
    }
    */


    // 6) Verdere verfijning van 5) met dynamische increment/decrement waarden
    /*
    const valueIncr = 10; // +10 for each increment
    const valueDecr = 10; // -10 for each decrement

    const [state, dispatch] = useReducer(function (state, action) {
        if (action.type == "INCR") state.value += action.value;
        if (action.type == "DECR") state.value -= action.value;
        return { ...state }; // Definitely do not write return state; !!!
    }, { value: 0 });

    function incrValue() {
        dispatch({ type: "INCR", value: valueIncr });
    }

    function decrValue() {
        dispatch({ type: "DECR", value: valueDecr });
    }
    */

    return (
        // 1) en 2)
        <>
            <button onClick={incrValue}>value + 1</button>
            &nbsp;&nbsp;
            <button onClick={decrValue}>value - 1</button>
            &nbsp;
            =&gt;
            value = {value};
        </>

        // 3), 4) en 5)
        /*
        <>
            <button onClick={incrValue}>value + 1</button>
            &nbsp;&nbsp;
            <button onClick={decrValue}>value - 1</button>
            &nbsp;
            =&gt;
            value = {state.value};
        </>
        */

        // 6)
        /*
        <>
            <button onClick={incrValue}>value + {valueIncr}</button>
            &nbsp;&nbsp;
            <button onClick={decrValue}>value - {valueDecr}</button>
            &nbsp;
            =&gt;
            value = {state.value};
        </>
        */
    )
}

export default Counter;