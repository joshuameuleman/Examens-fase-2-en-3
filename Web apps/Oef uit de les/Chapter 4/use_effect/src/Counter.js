import { useState, useEffect, useRef } from "react";

function Counter({ name }) {
    const [value, setValue] = useState(0);
    const valueRef = useRef(0);

    function incrValue() {
        setValue(value + 1);
    }

    function incrRef() {
        valueRef.current += 1;
    }

    // useEffect#1: used without conditions
    useEffect(function () {
        console.log(
            `${name} useEffect#1: value = ${value}, valueRef.current = ${valueRef.current}`
        );

        return function () {
            console.log(
                `${name} return useEffect#1: value = ${value}, valueRef.current = ${valueRef.current}`
            );
        };
    });

    // useEffect#2: used with conditions = []
    useEffect(function () {
        console.log(
            `${name} useEffect#2: value = ${value}, valueRef.current = ${valueRef.current}`
        );

        return function () {
            console.log(
                `${name} return useEffect#2: value = ${value}, valueRef.current = ${valueRef.current}`
            );
        };
    }, []);

    // useEffect#3: used with conditions = [valueRef.current]
    useEffect(function () {
        console.log(
            `${name} useEffect#3: value = ${value}, valueRef.current = ${valueRef.current}`
        );

        return function () {
            console.log(
                `${name} return useEffect#3: value = ${value}, valueRef.current = ${valueRef.current}`
            );
        };
    }, [valueRef.current]);

    console.log(`${name} Outside of useEffect()`);

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