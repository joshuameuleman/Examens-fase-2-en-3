import { BrowserRouter, Routes, Route, Link, NavLink } from "react-router-dom";
import Home from "./Home.js"
import About from "./About.js"
import { Products, CarProducts, BikeProducts } from "./Products.js"
import Info from "./Info.js"

//based on: https://www.w3schools.com/react/react_router.asp

// Style function for active links
const navLinkStyles = ({ isActive }) => ({
  color: isActive ? "#007bff" : '#000333',
  textDecoration: isActive ? "none" : "underline",
  fontWeight: isActive ? "bold" : "normal",
  padding: "5px 10px"
});

function App() {
  return (
    <BrowserRouter>
      <nav>
        <NavLink to="/" style={navLinkStyles}>Home</NavLink> {" | "}
        <NavLink to="/about" style={navLinkStyles}>About</NavLink> {" | "}
        <Link to="/products">Products</Link> {" | "}
        <Link to="/customer/Tobias">Tobias</Link> {" | "}
        <Link to="/customer/Linus">Linus</Link> {" | "}
        <Link to="/customer?firstname=Peter">Peter</Link>
      </nav>

      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/about" element={<About />} />
        <Route path="/products" element={<Products />}>
          <Route path="car" element={<CarProducts />} />
          <Route path="bike" element={<BikeProducts />} />
        </Route>
        <Route path="/customer/:firstname" element={<Info />} />
        <Route path="/customer" element={<Info />} />
      </Routes>
    </BrowserRouter>
  );
}

export default App;