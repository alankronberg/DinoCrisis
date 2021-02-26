class MapModel {
    constructor (DAO) {
        this.DAO = DAO
    }
  
    async createTable () {
        const sql = `
            CREATE TABLE IF NOT EXISTS Maps (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            filepath TEXT UNIQUE,
            name TEXT
        )`
        return await this.DAO.run(sql)
    }

    async addMap (filepath, name) {
        const sql = `INSERT INTO Maps (filepath, name) VALUES (?, ?)`;
        await this.DAO.run(sql, [filepath, name]);
    }

    async getMapList () {
        const sql = `SELECT id, name FROM Maps`;
        return await this.DAO.all(sql);
    }

    async getMap(id) {
        const sql = `SELECT filepath FROM Maps WHERE id = ?`;
        return await this.DAO.get(sql, [id]);
    }

}

module.exports = MapModel;