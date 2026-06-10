import { useState, useEffect } from "react";

const useFetch = function (url) {
    const [data, setData] = useState("");
    const [error, setError] = useState("");

    useEffect(function () {
        fetch(url)
            .then((res) => res.text())
            .then((data) => setData(data.toString()))
            .catch((err) => setError(err.toString()));
    }, [url]);

    return [data, error];
};

export default useFetch;