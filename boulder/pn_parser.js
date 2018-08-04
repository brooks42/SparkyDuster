class PushNotification {

    /**
     * 
     * @param {Object} obj a JSON object representing the body of the push notification
     */
    constructor(obj) {
        console.log(`New PushNotification created wiht body ${JSON.stringify(obj, undefined, '\t')}`);
        this.object = obj;
    }

    shouldPullRepoAndRebuild() {
        // TODO: not sure how to implement this yet haha
    }
};