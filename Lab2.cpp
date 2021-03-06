using namespace Akonadi;
using namespace KCal;

DueDateResource::DueDateResource( const QString &id ) 
{
	new SettingsAdaptor( Settings::self() );
	QDBusConnection::sessionBus().registerObject( QLatin1String( "/Settings" ), Settings::self(), QDBusConnection::ExportAdaptors );
	changeRecorder()->itemFetchScope().fetchFullPayload();
	netManager = 0;
	editManager = 0;
}
 
DueDateResource::~DueDateResource() 
{ 
	if (netManager) 
		delete netManager;
} 

void DueDateResource::retrieveCollections() 
{
	Collection c;
	c.setParent( Collection::root() );
	c.setRemoteId( "akonadi_duedate_resource_" + Settings::self()->course() + "_" + Settings::self()->semester());
	c.setName( Settings::self()->course() + "_" + Settings::self()->semester());
 	c.setContentMimeTypes( QStringList() << "application/x-vnd.akonadi.calendar.event" );
 	Collection::List list;
 	list << c;
 	collectionsRetrieved( list );
}

void DueDateResource::retrieveItems( const Akonadi::Collection &collection ) 
{	
	Q_UNUSED(collection);
	const QString course = Settings::self()->course();
	const QString semester = Settings::self()->semester();
 	if (!netManager){ 
		netManager = new QNetworkAccessManager(this);
 		connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
 	} 
	netManager->get(QNetworkRequest(QUrl(Settings::self()->url() + "?course=" + course + "&username=webuser&semester=" + semester)));
}

void DueDateResource::uploadFinished(QNetworkReply* reply)
{ 
	if (reply->error() == QNetworkReply::NoError){
		QString response;
		response = reply->readAll();
		if (response.indexOf("Success") >= 0){
			mPendingItem.setRemoteId(response.replace("Success: ", ""));
			changeCommitted(mPendingItem);
		} 
		else{ 
			emit error("Error Uploading Due Date: Server issued fail response.\n");
 			cancelTask();
 		} 
	} 
	else{
		emit error(QString("Error Uploading Due Date: %1.\n").arg(reply->errorString()));
 		cancelTask();
 	}
} 
