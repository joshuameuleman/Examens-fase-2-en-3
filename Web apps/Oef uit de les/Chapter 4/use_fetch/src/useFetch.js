import { useState, useEffect } from "react";

const useFetch = function (url) {
    const [data, setData] = useState("");
    const [error, setError] = useState("");

    useEffect(function () {
        fetch(url)
            .then((res) => res.text())
            .then((data) => setData(data.toString()))
            .catch((err) => setError(err.toString()));

        /*
        fetch(url)
            .then((res) => res.json())
            .then(function(data) { 
                console.log(data[0].name.common.toString()); 
                console.log(data.map((item) => item.name.common.toString())); 
                setData(data.map((item) => item.name.common.toString())); 
            } )
            .catch((err) => setError(err.toString()))
            ;
        */

        // Opmerking: i.p.v. te weken met .then() en .catch() kan je ook werken met "async" en "await". 
        // Gebruik de klassieke try-catch constructie om fouten op te vangen.
        // Meer info: zie boek p. 272
        //
        
    }, [url]);

    return [data, error];
};

export default useFetch;