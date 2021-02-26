const sqlite3 = require('sqlite3');
const util    = require('util');

function createDB (dbFilePath) {
    return new Promise ( (resolve, reject) => {
        const db = new sqlite3.Database(dbFilePath, (err) => {
            if (err) {
                console.error(`Could not open ${dbFilePath}`);
                reject(err);
            }
        })
        resolve(db);
    });
}


async function createDAO (dbFilePath) {
    const db = await createDB(dbFilePath);
    db.get = util.promisify(db.get);
    db.run = util.promisify(db.run);
    db.all = util.promisify(db.all);
    return db;
}

module.exports = createDAO;