const express = require("express");
const multer = require("multer");
const diskStorage = require("./multerStorage");
const createDAO = require('./Models/dao');
const path = require("path");
const MapModel = require('./Models/MapModel');

let Maps = undefined;

const mapUploader = multer({
    storage: diskStorage({
        destination(req, file, next){
            next(null, "maps");
        }
    }),
    fileFilter (req, file, next) {
        if(file.mimetype !== "application/octet-stream"){
            return next(new Error("Unexpected file type"));
        }
        next(null, true);
    }
});

const app = express();
app.use(express.static('maps'));
app.use(express.urlencoded({extended : true}));
app.use(express.json());
const dbFilePath = path.join(__dirname, "Database", "Maps.db")

app.get("/", (req, res) => {
    res.send("My power level is over 9000!!!!");
})

app.post("/uploadMap", mapUploader.single("map"), async (req, res) => {
    try{
        await Maps.addMap(req.file.path, req.body.name);
        res.send("Uploaded file!");
    }catch(err){
        console.log(err);
    }
});

app.get("/mapList", async (req, res) => {
    const list = await Maps.getMapList();
    console.log(list);
    res.send(JSON.stringify(list));
})

app.get("/map", async (req, res) => {
    console.log(req.query);
    if(req.query.id){
        try{
            const filepath = await Maps.getMap(parseInt(req.query.id));
            res.sendFile(path.join(__dirname, filepath.filepath));
        }catch(err){
            console.log(err);
            res.sendStatus(404);
        }
    }
    else{
        res.sendStatus(404);
    }
})

app.listen(9001, async () => {
    await initializeDB();
    console.log("Server listening on port 9001!");
});

async function initializeDB(){
    const dao = await createDAO(dbFilePath);
    Maps = new MapModel(dao);
    await Maps.createTable();
}