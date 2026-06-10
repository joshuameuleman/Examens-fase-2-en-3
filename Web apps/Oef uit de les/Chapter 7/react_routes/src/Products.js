import { Link, Outlet } from "react-router-dom";

function Products() {
  return (
    <div>
      <h1>Products page</h1>
      <nav style={{ marginBottom: "20px" }}>
        <Link to="/products/car">Cars</Link> { " | " }
        <Link to="/products/bike">Bikes</Link>
      </nav> 
      <Outlet /> 
    </div>
  );
}

//...

// note: you can split it up further into separate files:
function CarProducts() {
  return (
    <div>
      <h2>Cars</h2>
      <ul>
        <li>Audi</li>
        <li>BMW</li>
        <li>Volvo</li>
      </ul>
    </div>
  );
}

//...

function BikeProducts() {
  return (
    <div>
      <h2>Bikes</h2>
      <ul>
        <li>Yamaha</li>
        <li>Suzuki</li>
        <li>Honda</li>
      </ul>
    </div>
  );
}

//...

export { Products, CarProducts, BikeProducts }; // return multiple functions