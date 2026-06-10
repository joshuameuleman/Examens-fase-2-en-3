import useCounterMax from "./useCounterMax";

function Counter({ max }) {
    if (!max) max = 5; // If max is not specified, it defaults to 5
    const [value, incr, decr, error] = useCounterMax(max);

    function incrValue() {
        incr();
    }

    function decrValue() {
        decr();
    }

    return (
        // Opmerking: dit werkt ook: <button onClick={incr}>value + 1</button>
        <>
            <button onClick={incrValue}>value + 1</button>
            &nbsp;&nbsp;
            <button onClick={decrValue}>value - 1</button>
            &nbsp;
            =&gt;
            value = {value};<br />
            <b>{error}</b>
        </>
    )
}

export default Counter;