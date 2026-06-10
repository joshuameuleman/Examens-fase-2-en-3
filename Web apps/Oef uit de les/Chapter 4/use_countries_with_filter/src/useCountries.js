import useFetch from "./useFetch";

const useCountries = function (name) {
    const [data, error] = useFetch("https://restcountries.com/v3.1/all?fields=name");
    let countries;

    if (data) {
        countries = JSON.parse(data).map(function (elem) {
            return elem.name.common;
        });
        //countries = countries.sort((n1, n2) => (n1 > n2)); // werkt niet!
        countries = countries.sort();
        if (name) countries = countries.filter((n) => n.toUpperCase().includes(name.toUpperCase()));
    }

    return countries;
};

export default useCountries;