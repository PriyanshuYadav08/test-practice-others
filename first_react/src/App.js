import './App.css';

function App(){
    let a=4;
    let b=2;
    let c=a+b;
    return (
        <>
            {/* agar html ke jaise use karna h to outside {} */}
            {/* agar javascript ke jaise use karna h to inside {} */}
            {c+3}
            <h1 className="main">My first React App</h1>
            <p style={{
                backgroundColor:"pink"
                ,color:"blue",
                fontSize:"20px",
            }}>Welcome to my first React App</p>
            <div className='second'>
                <h1>
                    second line check
                </h1>
            </div>
        </>
    );
}

export default App;